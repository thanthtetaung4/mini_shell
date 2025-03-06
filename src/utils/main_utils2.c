
#include "../../header/minishell.h"

void	status_change(t_minishell *data)
{
	if (g_sig_status)
		data->status = 130;
	if (data->input == NULL)
		handle_eof(data);
}
