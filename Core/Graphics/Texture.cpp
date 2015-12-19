#include "Texture.hpp"
#include "../Utils/Output.hpp"


namespace Core {
	namespace Graphics {
		
		GLuint Texture::load(const char * texturePath) {
			using namespace gli;

			texture l_tex = gli::load(texturePath);

			if (l_tex.empty()) {
				ERROR_F("Failed to load %s", texturePath);
				return 0;
			}

			gl l_gl;
			gl::format const l_format = l_gl.translate(l_tex.format());
			GLenum l_target = l_gl.translate(l_tex.target());
			
			GLuint l_texID = 0;
			glGenTextures(1, &l_texID);
			glBindTexture(l_target, l_texID);
			glTexParameteri(l_target, GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameteri(l_target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(l_tex.levels() - 1));
			glTexParameteri(l_target, GL_TEXTURE_SWIZZLE_R, l_format.Swizzle[0]);
			glTexParameteri(l_target, GL_TEXTURE_SWIZZLE_G, l_format.Swizzle[1]);
			glTexParameteri(l_target, GL_TEXTURE_SWIZZLE_B, l_format.Swizzle[2]);
			glTexParameteri(l_target, GL_TEXTURE_SWIZZLE_A, l_format.Swizzle[3]);
			
			glm::tvec3<GLsizei> const l_dimensions(l_tex.dimensions());
			GLsizei const l_faceTotal = static_cast<GLsizei>(l_tex.layers() * l_tex.faces());

			switch (l_tex.target()) {
				case TARGET_1D:
					glTexStorage1D(l_target, static_cast<GLint>(l_tex.levels()), l_format.Internal, l_dimensions.x);
					break;
				case TARGET_1D_ARRAY:
				case TARGET_2D:
				case TARGET_CUBE:
					glTexStorage2D(l_target, static_cast<GLint>(l_tex.levels()), l_format.Internal, l_dimensions.x, 
						(l_tex.target() == TARGET_2D)? l_dimensions.y : l_faceTotal);
					break;
				case TARGET_2D_ARRAY:
				case TARGET_3D:
				case TARGET_CUBE_ARRAY:
					glTexStorage3D(l_target, static_cast<GLint>(l_tex.levels()), l_format.Internal, l_dimensions.x, l_dimensions.y,
						(l_tex.target() == TARGET_3D)? l_dimensions.z : l_faceTotal);
					break;
				default:
					ERROR("Wrong target...");
					assert(0);
					break;
			}

			for (size_t layer = 0; layer < l_tex.layers(); layer++)
				for (size_t face = 0; face < l_tex.faces(); face++)
					for (size_t level = 0; level < l_tex.levels(); level++) {
						GLsizei const l_layerGL = static_cast<GLsizei>(layer);
						glm::tvec3<GLsizei> l_dimensions(l_tex.dimensions(level));
						l_target = (is_target_cube(l_tex.target())) ? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face) : l_target;

						switch (l_tex.target()) {
							case TARGET_1D:
								if (is_compressed(l_tex.format()))
									glCompressedTexSubImage1D(l_target, static_cast<GLint>(level), 0, l_dimensions.x, 
										l_format.Internal, static_cast<GLsizei>(l_tex.size(level)), l_tex.data(layer, face, level));
								else
									glTexSubImage1D(l_target, static_cast<GLint>(level), 0, l_dimensions.x,
										l_format.External, l_format.Type, l_tex.data(layer, face, level));
							case TARGET_1D_ARRAY:
							case TARGET_2D:
							case TARGET_CUBE:
								if (is_compressed(l_tex.format()))
									glCompressedTexSubImage2D(l_target, static_cast<GLint>(level), 0, 0, l_dimensions.x,
										(l_tex.target() == TARGET_1D_ARRAY)? l_layerGL : l_dimensions.y, l_format.Internal,
										static_cast<GLsizei>(l_tex.size(level)), l_tex.data(layer, face, level));
								else
									glTexSubImage2D(l_target, static_cast<GLint>(level), 0, 0, l_dimensions.x,
										(l_tex.target() == TARGET_1D_ARRAY) ? l_layerGL : l_dimensions.y, l_format.External,
										l_format.Type, l_tex.data(layer, face, level));
								break;
							case TARGET_2D_ARRAY:
							case TARGET_3D:
							case TARGET_CUBE_ARRAY:
								if (is_compressed(l_tex.format()))
									glCompressedTexSubImage3D(l_target, static_cast<GLint>(level), 0, 0, 0, l_dimensions.x, l_dimensions.y,
										(l_tex.target() == TARGET_3D) ? l_dimensions.z : l_layerGL, l_format.Internal,
										static_cast<GLsizei>(l_tex.size(level)), l_tex.data(layer, face, level));
								else
									glTexSubImage3D(l_target, static_cast<GLint>(level), 0, 0, 0, l_dimensions.x, l_dimensions.y,
										(l_tex.target() == TARGET_3D) ? l_dimensions.z : l_layerGL, l_format.External,
										l_format.Type, l_tex.data(layer, face, level));
								break;
							default:
								ERROR("Wrong target...");
								assert(0);
								break;
						}
					}
			return l_texID;
		}

		GLboolean Texture::load2D(const char* texturePath, GLboolean withMipMaps) {
			FREE_IMAGE_FORMAT format = FreeImage_GetFileType(texturePath);

			if (format == FIF_UNKNOWN)
				format = FreeImage_GetFIFFromFilename(texturePath);

			if (format == FIF_UNKNOWN)
				return GL_FALSE;

			FIBITMAP* bits;

			if (FreeImage_FIFSupportsReading(format))
				bits = FreeImage_Load(format, texturePath);

			if (!bits)
				return false;

			BYTE* data = FreeImage_GetBits(bits);
			width = FreeImage_GetWidth(bits);
			height = FreeImage_GetHeight(bits);
			bytesPerPixel = FreeImage_GetBPP(bits);

			if (data == 0 || width == 0 || height == 0)
				return GL_FALSE;

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			GLuint spFormat = (bytesPerPixel == 24) ? GL_BGR : (bytesPerPixel == 8) ? GL_LUMINANCE : 0;
			GLuint inFormat = (bytesPerPixel == 24) ? GL_RGB : GL_DEPTH_COMPONENT;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, spFormat, GL_UNSIGNED_BYTE, data);

			if (withMipMaps)
				glGenerateMipmap(GL_TEXTURE_2D);

			FreeImage_Unload(bits);

			glGenSamplers(1, &textureSampler);

			return GL_TRUE;
		}

		void Texture::setFiltering(GLint magnification, GLint minification) const {
			glSamplerParameteri(textureSampler, GL_TEXTURE_MAG_FILTER, magnification);
			glSamplerParameteri(textureSampler, GL_TEXTURE_MIN_FILTER, minification);
		}
		
		void Texture::setCubeBoxParam() const {
			glSamplerParameteri(textureSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glSamplerParameteri(textureSampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glSamplerParameteri(textureSampler, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		void Texture::bind(GLuint unit) const {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glBindSampler(unit, textureSampler);
		}
	}
}
