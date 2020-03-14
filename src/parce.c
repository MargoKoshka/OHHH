#include "rtv1.h" 

static void	init_konys(t_rtv *p, char **tab, int i)
{
    p->object[i] = (t_object *)malloc(sizeof(t_object));
	p->object[i]->id = (int)"K";
	p->object[i]->norm_p.x = ft_atof(tab[1]);
	p->object[i]->norm_p.y = ft_atof(tab[2]);
	p->object[i]->norm_p.z = ft_atof(tab[3]);
	p->object[i]->angle = ft_atof(tab[4]);
	p->object[i]->pos.x = ft_atof(tab[5]);
	p->object[i]->pos.y = ft_atof(tab[6]);
	p->object[i]->pos.z = ft_atof(tab[7]);
	p->object[i]->angle_n.x = ft_atof(tab[8]);
	p->object[i]->angle_n.y = ft_atof(tab[9]);
	p->object[i]->angle_n.z = ft_atof(tab[10]);
	p->object[i]->color = ft_ahextocolor(tab[11]);
	p->object[i]->specular = ft_atof(tab[12]);
	ft_rotat_vector(&p->object[i]->angle_n, &p->object[i]->norm_p);
	object_data(p->object[i], &p->camera->start);
}

static void	init_cylind(t_rtv *p, char **tab, int i)
{
    p->object[i] = (t_object *)malloc(sizeof(t_object));
	p->object[i]->id = (int)"C";
	p->object[i]->norm_p.x = ft_atoi(tab[1]);
	p->object[i]->norm_p.y = ft_atoi(tab[2]);
	p->object[i]->norm_p.z = ft_atoi(tab[3]);
	p->object[i]->pos.x = ft_atoi(tab[4]);
	p->object[i]->pos.y = ft_atoi(tab[5]);
	p->object[i]->pos.z = ft_atoi(tab[6]);
	p->object[i]->radius = ft_atof(tab[7]);
	p->object[i]->angle_n.x = ft_atof(tab[8]);
	p->object[i]->angle_n.y = ft_atof(tab[9]);
	p->object[i]->angle_n.z = ft_atof(tab[10]);
	p->object[i]->color = ft_ahextocolor(tab[11]);
	p->object[i]->specular = ft_atof(tab[12]);
	ft_rotat_vector(&p->object[i]->angle_n, &p->object[i]->norm_p);
	object_data(p->object[i], &p->camera->start);
}

static void	init_plane(t_rtv *p, char **tab, int i)
{
    p->object[i] = (t_object *)malloc(sizeof(t_object));
	p->object[i]->id = (int)"P";
	p->object[i]->norm_p.x = ft_atoi(tab[1]);
	p->object[i]->norm_p.y = ft_atoi(tab[2]);
	p->object[i]->norm_p.z = ft_atoi(tab[3]);
	p->object[i]->pos.x = ft_atoi(tab[4]);
	p->object[i]->pos.y = ft_atoi(tab[5]);
	p->object[i]->pos.z = ft_atoi(tab[6]);
	p->object[i]->angle_n.x = ft_atof(tab[7]);
	p->object[i]->angle_n.y = ft_atof(tab[8]);
	p->object[i]->angle_n.z = ft_atof(tab[9]);
	p->object[i]->color = ft_ahextocolor(tab[10]);
	p->object[i]->specular = ft_atof(tab[1]);
    p->object[i]->norm_p = ft_rotation_vector(&p->object[i]->angle_n, &p->object[i]->norm_p);
	object_data(p->object[i], &p->camera->start);
}

static void	init_sphere(t_rtv *p, char **tab, int i)
{
    p->object[i] = (t_object *)malloc(sizeof(t_object));
	if (p->object[0] == NULL)
		ft_exit(0);
	p->object[i]->id = (int)"S";
	p->object[i]->pos.x = ft_atoi(tab[1]);
	p->object[i]->pos.y = ft_atoi(tab[2]);
	p->object[i]->pos.z = ft_atoi(tab[3]);
	p->object[i]->radius = ft_atof(tab[4]);
	p->object[i]->color = ft_ahextocolor(tab[5]); // GOLD 0xFFD700 FUCHSIA 0xFF00FF
	p->object[i]->specular = ft_atof(tab[6]);
	object_data(p->object[i], &p->camera->start);
}

static void	init_light(t_rtv *p, char **tab, int i)
{
    p->light->pos.x = ft_atoi(tab[1]);
	p->light->pos.y = ft_atoi(tab[2]);
	p->light->pos.z = ft_atoi(tab[3]);
	p->light->intensity = ft_atof(tab[4]);
	p->light->color = ft_ahextocolor(tab[5]);
	p->light->pos = ft_subtraction_vector(&p->light->pos, &p->camera->start);
}

static void	add_obj_to_tab(t_rtv *paint, char **tab, int i)
{
	if (!ft_strcmp(tab[i], "Light"))
        init_light(paint, tab, i);
	else if (!ft_strcmp(tab[i], "Sphere"))
        init_sphere(paint, tab, i);
	else if (!ft_strcmp(tab[i], "Plane"))
		init_plane(paint, tab, i);
	else if (!ft_strcmp(tab[i], "Cylind"))
	    init_cylind(paint, tab, i);
	else if (!ft_strcmp(tab[i], "Konys"))
	    init_konys(paint, tab, i);
}

static int		ft_freetab(char **tab)
{
	int		i;

	if (!tab)
		return (0);
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (0);
}

void	init_tab_obj(t_rtv *paint, char *src)
{
	int		i;
	int		fd;
	char	*line;
	char	**tab;

	line = NULL;
    i = 0;
	if ((fd = open(src, O_RDONLY)) <= 0)
		ft_exit("error can't open file\n");
	get_next_line(fd, &line), tab = ft_strsplit(line, ' ');
	while (get_next_line(fd, &line) > 0)
	{
		add_obj_to_tab(paint, tab, i);
        i++;
		ft_freetab(tab);
		free(line);
	}
}