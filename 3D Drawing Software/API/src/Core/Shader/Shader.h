#pragma once

#include <unordered_map>
#include <string>
#include "../../Core/Mat4/Matrix4.h"
#include "../DLLBuild.h"

namespace dra {
	
	struct _API ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
	};

	class _API Shader {
		public:
			Shader(const std::string& filepath);
			~Shader();

			void Bind() const;
			void Unbind() const;
			
			void SetUniform1i(const std::string& name, int value);
			void SetUniform1f(const std::string& name, float value);
			void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
			void SetUniformMat4f(const std::string& name, const Matrix4<float>& matrix);

		private:
			unsigned int m_RendererID;
			std::string m_FilePath;
			mutable std::unordered_map<std::string, int> m_UniformLocationCache;

			ShaderProgramSource ParseShader(const std::string& filepath);
			unsigned int CompileShader(unsigned int type, const std::string& source);
			unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
			int GetUniformLocation(const std::string& name) const;
	};
}