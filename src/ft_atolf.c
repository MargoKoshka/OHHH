#include "rtv1.h"

double		ft_atof(const char *str)
{
	double	result;
	int		i;

	result = (double)ft_atoi(str);
	i = ft_len_untill(str, '.');
	if (i && str[i])
	{
		if (result >= 0 && str[0] != '-')
			result += ((double)ft_atoi(str + i + 1))
				/ ((ft_strlen(str + i + 1) * 10));
		else
			result -= ((double)ft_atoi(str + i + 1))
				/ ((ft_strlen(str + i + 1) * 10));
	}
	return (result);
}



int		ft_ahextocolor(char *ahex)
{
	char	*str;
	char	*tmp;
	int		c;
	int		res;

	str = ft_strdup(ahex);
	str[2] = '\0';
	tmp = ft_convert_base(str, "0123456789ABCDEF", "0123456789");
	c = ft_atoi(tmp);
	res = c << 16;
	free(str);
	free(tmp);
	str = ft_strdup(ahex + 2);
	str[2] = '\0';
	tmp = ft_convert_base(str, "0123456789ABCDEF", "0123456789");
	c = ft_atoi(tmp);
	res |= c << 8;
	free(str);
	free(tmp);
	str = ft_strdup(ahex + 4);
	tmp = ft_convert_base(str, "0123456789ABCDEF", "0123456789");
	res |= ft_atoi(tmp);
	free(str);
	free(tmp);
	return (res);
}