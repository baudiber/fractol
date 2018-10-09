/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:44:25 by baudiber          #+#    #+#             */
/*   Updated: 2018/10/08 18:37:47 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		quittest(void)
{
	exit(1);
	return (0);
}


GLuint	gen_texture(void)
{
	GLuint	tex_handle;
	GLenum	e;
	
	glGenTextures(1, &tex_handle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 512, 512, 0, GL_RED, GL_FLOAT, NULL);
	//bind it to an image as well
	printf("Test\n");
	glBindImageTexture(0, tex_handle, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);
	printf("Test\n");
	e = glGetError();	
	if (e != GL_NO_ERROR)
	{
		ft_putendl("gl error");
		exit (0);
	}
	return (tex_handle);
}

void	arrays_and_buffers(GLuint *prog_hdl)
{
	GLuint	vert_array;
	GLuint	pos_buf;
	GLint	posPtr;
	GLenum	e;
	float	data[] = {
		-1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f
	};

	glGenVertexArrays(1, &vert_array);
	glBindVertexArray(vert_array);
	glGenBuffers(1, &pos_buf);
	glBindBuffer(GL_ARRAY_BUFFER, pos_buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8, data, GL_STREAM_DRAW);
	posPtr = glGetAttribLocation(*prog_hdl, "pos");	
	glVertexAttribPointer(posPtr, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posPtr);
	e = glGetError();	
	if (e != GL_NO_ERROR)
	{
		ft_putendl("gl error");
		exit (0);
	}
}

GLuint	gen_renderprogram(void)
{
	GLuint	prog_hdl;
	GLuint	vp;
	GLuint	fp;
	int		rvalue;
	const char *vpSrc[] = {
		"#version 430\n",
		"in vec2 pos;\
		out vec2 texCoord;\
		void main() {\
			texCoord = pos * 0.5f + 0.5f;\
			gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);\
		}"
	};

	const char *fpSrc[] = {
		"#version 430\n",
		"uniform sampler2D srcTex;\
		in vec2 texCoord;\
		out	vec4 color;\
		void main() {\
			float c = texture(srcTex, texCoord).x;\
			color = vec4(c, 1.0, 1.0, 1.0);\
		}"
	};


	prog_hdl = glCreateProgram();
	vp = glCreateShader(GL_VERTEX_SHADER);
	fp = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vp, 2, vpSrc, NULL);
	glShaderSource(fp, 2, fpSrc, NULL);
	glCompileShader(vp);
	glGetShaderiv(vp, GL_COMPILE_STATUS, &rvalue);
	if (!rvalue)
	{
		ft_putendl("error compiling vp shader");
		exit(0);
	}
	glAttachShader(prog_hdl, vp);
	glCompileShader(fp);
	glGetShaderiv(fp, GL_COMPILE_STATUS, &rvalue);
	if (!rvalue)
	{
		ft_putendl("error compiling fp shader");
		exit(0);
	}
	glAttachShader(prog_hdl, fp);
	glBindFragDataLocation(prog_hdl, 0, "color");
	glLinkProgram(prog_hdl);
	glGetProgramiv(prog_hdl, GL_LINK_STATUS, &rvalue);
	if (!rvalue)
	{
		ft_putendl("error compiling sp");
		exit(0);
	}
	glUseProgram(prog_hdl);
	glUniform1i(glGetUniformLocation(prog_hdl, "srcTex"), 0);
	arrays_and_buffers(&prog_hdl);
	return (prog_hdl);
}

GLuint	gen_computeprog(void)
{
	GLuint	prog_hdl;
	GLuint	cs;
	GLenum	e;
	int		rvalue;
	const char	*csSrc[] = {
		"#version 430\n",
		"uniform float roll;\
		uniform image2D destTex;\
		layout (local_size_x = 16, local_size_y = 16) in;\
		void main() {\
			ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);\
			float localCoef = length(vec2(ivec2(gl_LocalInvocationID.xy) - 8) / 8.0);\
			float globalCoef = sin(float(gl_WorkGroupID.x + gl_WorkGroupID.y) * 0.1 + roll) * 0.5;\
			imageStore(destTex, storePos, vec4(1.0 - globalCoef * localCoef, 0.0, 0.0, 0.0));\
		}"
	};

	prog_hdl = glCreateProgram();
	cs = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(cs, 2, csSrc, NULL);
	glCompileShader(cs);
	glGetShaderiv(cs, GL_COMPILE_STATUS, &rvalue);
	if (!rvalue)
	{
		ft_putendl("Error in compiling the CS");
		GLchar log[10240];
		GLsizei length;
		glGetShaderInfoLog(cs, 10239, &length, log);
		fprintf(stderr, "Compiler log:\n%s\n", log);
		exit (0);
	}
	glAttachShader(prog_hdl, cs);
	glLinkProgram(prog_hdl);
	glGetProgramiv(prog_hdl, GL_LINK_STATUS, &rvalue);
	if (!rvalue)
	{
		ft_putendl("Error in linking the CS");
		GLchar log[10240];
		GLsizei length;
		glGetShaderInfoLog(cs, 10239, &length, log);
		fprintf(stderr, "Linker log:\n%s\n", log);
		exit (0);
	}
	glUseProgram(prog_hdl);
	glUniform1i(glGetUniformLocation(prog_hdl, "destTex"), 0);
	e = glGetError();	
	if (e != GL_NO_ERROR)
	{
		ft_putendl("gl error");
		exit (0);
	}
	return (prog_hdl);
}

void	get_rendertarget(t_gl *gl)
{
	glViewport(0, 0, 800, 600);
	gl->tex_hdl = gen_texture();
	gl->render_hdl = gen_renderprogram();
	gl->compute_hdl = gen_computeprog();
}

void	init_gl(t_setup *stp)
{
	GLenum GlewInitResult;
	
	stp->mlx = mlx_init();
	stp->win = mlx_new_opengl_window(stp->mlx, 800, 600, stp->av);
	GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) {
		fprintf(
				stderr,
				"ERROR\n"
			   );
		exit(EXIT_FAILURE);
	}
	get_rendertarget(&stp->gl);
}

void	update_tex(int	frame, t_gl *gl)
{
	GLenum e;

	glUseProgram(gl->compute_hdl);
	glUniform1f(glGetUniformLocation(gl->compute_hdl, "roll"), (float)frame * 0.01f);
	glDispatchCompute(512 / 16, 512 / 16, 1); //512^2 threads in blocks of 16^2
	e = glGetError();	
	if (e != GL_NO_ERROR)
	{
		ft_putendl("gl error");
		exit (0);
	}

}

void	drawframe(t_setup *stp)
{
	glUseProgram(stp->gl.render_hdl);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void	render_loop(t_setup *stp)
{
	int		i;

	i = 0;
	while (i < 1024)
	{
		update_tex(i, &stp->gl);
		drawframe(stp);
		i++;
	}
}

void	gl_main(t_setup *stp)
{
	init_gl(stp);
	render_loop(stp);
	mlx_hook(stp->win, 17, 0L, quittest, NULL);
	mlx_opengl_swap_buffers(stp->win);
	//mlx_key_hook(stp->win, stp_key, &stp);
	mlx_loop(stp->mlx);
}
