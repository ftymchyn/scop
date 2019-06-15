#include "scop.h"

void	render_model(t_darr *models)
{
	t_model	*model;
	t_mesh	*mesh;
	size_t	i;
	size_t	k;

	i = 0;
	while (i < models->size)
	{
		model = (t_model*)darr_at(models, i);
		k = 0;
		while (k < model->meshes.size)
		{
			mesh = (t_mesh*)darr_at(&model->meshes, k);
			glBindVertexArray(mesh->vao);
			glDrawArrays(GL_TRIANGLES, 0, mesh->v.size);
			glBindVertexArray(0);
			k++;
		}
		i++;
	}
}