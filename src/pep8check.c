/*
 * Copyright (C) 2007 Gabriel Falcão <gabriel@guake-terminal.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "lib/libpep8.h"

int
main (int argc, char *argv[])
{
  gchar *contents, *width_check_result;
  gchar **files_list = NULL;
  GError *error = NULL;
  GOptionEntry options[] = {
    {"arquivos", 'f', G_OPTION_FLAG_IN_MAIN, G_OPTION_ARG_FILENAME_ARRAY,
     &files_list, "Lista de arquivos a serem checados", NULL}
  };
  GOptionContext *option_context =
    g_option_context_new (" - valida codigos python segundo a PEP-8");
  g_option_context_add_main_entries (option_context, options, NULL);
  g_option_context_parse (option_context, &argc, &argv, &error);

  if (!files_list)
    {
      gchar *tmp_help;
      tmp_help = g_option_context_get_help (option_context, FALSE, NULL);
      printf ("%s", tmp_help);
      g_free (tmp_help);
      return 1;
    }
  else
    {

      while (*files_list)
        {
          g_file_get_contents ((*files_list), &contents, NULL, NULL);
          if (contents)
            {
              width_check_result = check_linewidth (contents);
              if (width_check_result != NULL)
                {
                  printf
                    ("\e[1;35mVerificando o arquivo \e[1;33m%s\e[0m\n",
                     (*files_list));
                  printf (width_check_result);
                }
            }
          else
            {
              printf
                ("\e[1;31mO arquivo \e[1;33m%s\e[1;31m nao existe\e[0m",
                 (*files_list));
            }
          files_list++;
        }
    }
  g_free(option_context);
  return 0;
}
