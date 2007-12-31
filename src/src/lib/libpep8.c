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
 *f* License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * HOW TO COMPILE
 * gcc -Wall -Wextra -Werror `pkg-config --libs --cflags glib-2.0 ` THIS_FILENAME.c -o OUTPUT_FILENAME
 *
 */
#include "libpep8.h"

extern char *
check_linewidth (char *contents)
{
  if (contents == NULL)
    {
      return NULL;
    }
  GRegex *expression, *replacer;
  guint total_overline, cnt, curlen;
  gchar **parts, *current, *return_str, *fline, *concat;
  return_str = "";
  expression =
    g_regex_new ("\n", G_REGEX_DOTALL, G_REGEX_MATCH_NEWLINE_ANY, NULL);
  replacer =
    g_regex_new ("^[ ]*", G_REGEX_DOTALL, G_REGEX_MATCH_NEWLINE_ANY, NULL);
  parts = g_regex_split (expression, contents, G_REGEX_MATCH_NEWLINE_ANY);
  total_overline = 0;
  cnt = 1;
  while (*parts)
    {
      curlen = strlen ((*parts));
      if (curlen > 80)
        {
          total_overline++;
          current =
            g_regex_replace (replacer, (*parts), -1, 0, "",
                             G_REGEX_MATCH_NEWLINE_ANY, NULL);
          fline = g_strdup_printf ("%.*s", 10, current);
          concat = g_strdup_printf
            ("\e[1;33m >>> \e[1;37m%s...\e[1;34m # linha %d, ultrapassou 80 caracteres, \e[1;31mpossui %d caracteres\e[0m \n",
             fline, cnt, curlen);
          return_str = g_strconcat (return_str, concat, NULL);
        }
      cnt++;
      parts++;
    }
  if (total_overline > 0)
    {
      concat = g_strdup_printf
        ("\e[1;32mTotal de linhas que ultrapassam 79 caracteres: %d\e[0m\n",
         total_overline);
      return_str = g_strconcat (return_str, concat, NULL);
    }
  else
    {
      return_str = NULL;
    }
  g_free (expression);
  g_free (replacer);
  g_free (concat);

  return return_str;

}
