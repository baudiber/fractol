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

void	render_loop(t_setup *stp)
{
	(void)stp;
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void	get_rendertarget(t_gl *gl)
{
	gl->buffer = 0;
	glGenFramebuffers(1, &gl->buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gl->buffer);
	glGenTextures(1, &gl->buffer);
	glBindTexture(GL_TEXTURE_2D, gl->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gl->texture, 0);
//	gl->buffers[0] = GL_COLOR_ATTACHMENT0;
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers);
	//if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	//	exit(0);
	glBindFramebuffer(GL_FRAMEBUFFER, gl->buffer);
	glViewport(0,0,1024,768);
}

void	create_fbo(void)
{
	GLuint quad_VertexArrayID;
	glGenVertexArrays(1, &quad_VertexArrayID);
	glBindVertexArray(quad_VertexArrayID);

	static const GLfloat g_quad_vertex_buffer_data[] = {
	    -1.0f, -1.0f, 0.0f,
	    1.0f, -1.0f, 0.0f,
	    -1.0f,  1.0f, 0.0f,
	    -1.0f,  1.0f, 0.0f,
	    1.0f, -1.0f, 0.0f,
	    1.0f,  1.0f, 0.0f,
	};

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0,1024,768);
}

void	init_gl(t_setup *stp)
{
	GLenum GlewInitResult;
	
	stp->mlx = mlx_init();
	stp->win = mlx_new_opengl_window(stp->mlx, 1024, 768, stp->av);
	GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) {
		fprintf(
				stderr,
				"ERROR\n"
			   );
		exit(EXIT_FAILURE);
	}
	get_rendertarget(&stp->gl);
	create_fbo();
}

void	gl_main(t_setup *stp)
{
	init_gl(stp);
	render_loop(stp);
	mlx_opengl_swap_buffers(stp->win);
	//mlx_hook(stp->win, 17, 0L, quittest, NULL);
	mlx_key_hook(stp->win, stp_key, &stp);
	mlx_loop(stp->mlx);
}
