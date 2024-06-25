/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:15:24 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/25 12:31:26 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE	16
# endif

# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>

# include "libgc.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

double	ft_gettime(void);

size_t	ft_gnlstrlen(const char *str);
char	*ft_gnlstrjoin(char *s1, char *s2, t_garb *gc);
char	*ft_gnlstrchr(char *str, int c);
int		gnl(int fd, char **line, t_garb *gc);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

void	*ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_close(int n_args, ...);
void	ft_free(void *ptr);

char	*ft_domstr(char *str, size_t start, size_t end, t_garb *gc);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s, t_garb *gc);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len, t_garb *gc);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char	*ft_strjoin(const char *s1, const char *s2, t_garb *gc);
char	*ft_itoa(int n, t_garb *gc);
char	*ft_strtrim(const char *s1, const char *set, t_garb *gc);
char	**ft_split(const char *s, char c, t_garb *gc);

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *str);
int 	ft_ptoi(char **str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_lstsize(t_list *lst);
int		ft_countw(const char *s, char c);

#endif
