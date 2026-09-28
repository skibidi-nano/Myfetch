#include "distro.h"

int kernel_fetch(int fd)
{
   char buffer[BUFFER_SIZE];
   char line_buffer[SECONDARY_BUFFER_SIZE];
   int line_buffer_index = 0;

   char* print_string; 
   int text_y = TEXT_Y_INIT + KERNEL_OFFSET;

   lseek(fd, 0, SEEK_SET); // reset file descriptor

   ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
   if (bytes_read <= 0) 
   {
      return 1;
   }
   buffer[bytes_read] = '\0';

            
   for (int i = 0; i < bytes_read; i++)
   {
      line_buffer[line_buffer_index] = buffer[i];
      if(line_buffer[line_buffer_index] == '(')
      {
         line_buffer[line_buffer_index - 1] = '\0';
         line_buffer_index = 0;

         print_string = "Kernel version - ";
         mvprintw(text_y, TEXT_X, "%s", print_string);

         mvprintw(text_y, TEXT_X + strlen(print_string), "%s", line_buffer);

         break;

      }
      else
      {
         line_buffer_index++;
      }
   } 

   return 0;

}

int distro_fetch(int fd)
{
   char buffer[BUFFER_SIZE];
   char line_buffer[SECONDARY_BUFFER_SIZE];
   int line_buffer_index = 0;
   char string_buffer[SECONDARY_BUFFER_SIZE];
   char read_buffer[SECONDARY_BUFFER_SIZE];
   int read_buffer_index = 0;
   
   int strlength;
   int length_string_buffer;

   char* print_string; 
   int text_y = 0;

   parse_mapping mappings[] = 
   {
   //Codeword    Whats printed      y-offset
   //.key         .label        .offset
   {"PRETTY_NAME",    "OS - ",      PRETTY_NAME_OFFSET},
   {"ID",             "PLACEHOLDER", NO_OFFSET} //in this case we only parse so we can call the correct function for the ascii
   };
   int num_mappings = sizeof(mappings) / sizeof(mappings[0]);

   lseek(fd, 0, SEEK_SET); // reset file descriptor

   ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
   if (bytes_read <= 0) 
   {
      return 1;
   }
   buffer[bytes_read] = '\0';

            
   for (int i = 0; i < bytes_read; i++)
   {
      line_buffer[line_buffer_index] = buffer[i];
      if(line_buffer[line_buffer_index] == '\n')
      {
         line_buffer[line_buffer_index] = '\0';
         line_buffer_index = 0;

         strlength = strlen(line_buffer);
         for (int j = 0; j < strlength; j++)
         {
            string_buffer[j] = line_buffer[j];

            if(string_buffer[j] == '=')
            {
               string_buffer[j] = '\0';
               break;
            }
         }

         for (int j = 0; j < num_mappings; j++)
         {
            if(!strcmp(string_buffer, mappings[j].key))
            {
               strlength = (strlen(line_buffer) - strlen(string_buffer));
               length_string_buffer = strlen(string_buffer);
               for (int k = 0; k < strlength; k++)
               {
                  if (line_buffer[k + length_string_buffer] != '=' && line_buffer[k + length_string_buffer] != '"')
                  {
                     read_buffer[read_buffer_index] = line_buffer[k + length_string_buffer];
                     read_buffer_index++;
                  }
               }

               read_buffer[read_buffer_index] = '\0';


               
               if (!strcmp(mappings[j].key, "PRETTY_NAME"))
               {
                  offset = mappings[j].y_offset; //manipulte the global offset (maybe overall change the offset concept)
                  text_y = TEXT_Y_INIT + offset; // calculate the y variable
                  print_string = mappings[j].label;
                  mvprintw(text_y, TEXT_X, "%s", print_string);
                  mvprintw(text_y, TEXT_X + strlen(print_string), "%s", read_buffer);
               }
               else if ((!strcmp(mappings[j].key, "ID")))
               {
                  distro_ascii(read_buffer);
               }
               
               read_buffer_index = 0;  
            }
         }
      }
      else
      {
         line_buffer_index++;
      }
   }

   return 0;
}

void distro_ascii(char *distro)
{
   char **ascii_art = NULL;

   if (!strcmp(distro, "nixos"))
   {
      ascii_art = nixos_ascii();
   }
   else if(!strcmp(distro, "debian"))
   {
      ascii_art = debian_ascii();
   }
   else if(!strcmp(distro, "arch"))
   {
      ascii_art = arch_ascii();
   }
   else if(!strcmp(distro, "ubuntu"))
   {
      ascii_art = ubuntu_ascii();
   }
   else if(!strcmp(distro, "gentoo"))
   {
      ascii_art = gentoo_ascii();
   }
   else
   {
      unsupported_ascii();
   }

   for (int i = 0; ascii_art[i] != NULL; i++) 
   {
      mvprintw(ASCII_COORD_Y + i, ASCII_COORD_X, "%s", ascii_art[i]);
   }
}

char **nixos_ascii(void)
{
   static char *art[] = 
   {
                                       
   "           __    ____    __           ",
   "          /  \\   \\   \\  /  \\         ",
   "          \\   \\   \\   \\/   /          ", 
   "        ___\\   \\___\\      /           ",
   "       /            \\    /   /\\      ",
   "      /______________\\   \\  /  \\     ",
   "           /   /      \\   \\/   /      ",
   "    ______/   /        \\  /   /___    ",
   "   /         /          \\/        \\  ",
   "   \\____    /\\          /   ______/   ",
   "       /   /  \\        /   /          ",
   "      /   /\\   \\______/___/_____      ",
   "      \\  /  \\   \\              /      ",
   "       \\/   /    \\____    ____/       ",
   "           /      \\   \\   \\          ",
   "          /   /\\   \\   \\   \\         ",
   "          \\__/  \\___\\   \\__/          ",
      NULL
   };
   
   return art;
}

char **debian_ascii(void)
{
   static char *art[] = 
   {
      "          _,met$$$$$gg.        ",
      "       ,g$$$$$$$$$$$$$$$P.     ",
      "     ,g$$P\"\"       \"\"\"Y$$.\".   ",
      "    ,$$P'              `$$$.   ",
      "  ',$$P       ,ggs.     `$$b:  ",
      "  `d$$'     ,$P\"'   .    $$$   ",
      "  $$P      d$'     ,    $$P    ",
      "  $$:      $$.   -    ,d$$'    ",
      "  $$;      Y$b._   _,d$P'      ",
      "  Y$$.    `.`\"Y$$$$P\"'         ",
      "  `$$b      \"-.__              ",
      "   `Y$$b                       ",
      "    `Y$$.                      ",
      "     `$$b.                     ",
      "       `Y$$b.                  ",
      "         `\\\"Y$b._               ",
      "             `\"\"\"\"             ",
      NULL
   };
   
   return art;
}

char **arch_ascii(void)
{
   static char *art[] = 
   {
   "                  -@         ",               
   "                .##@         ",
   "               .####@        ",
   "               @#####@       ",
   "             . *######@      ",
   "            .##@o@#####@     ",
   "           /############@    ",
   "          /##############@   ",
   "         @######@**\%######@ ",
   "        @######`     \%#####o ",
   "       @######@       ######\% ",
   "     -@#######h       ######@.` ",
   "    /#####h**``       `**\%@####@ ",
   "   @H@*`                    `*\%#@ ",
   "  *`                            `* ",
      NULL
   };
   
   return art;
}

char **ubuntu_ascii(void) // NEEDS REWORK TOO LARGE //////////////////////////////////////////////////////////////////////////////
{
   static char *art[] = 
   {
   "                                   ....",
   "                .',:clooo:  .:looooo:.",
   "             .;looooooooc  .oooooooooo'",
   "          .;looooool:,''.  :ooooooooooc ",
   "         ;looool;.         'oooooooooo, ",
   "        ;clool'             .cooooooc.  ,, ",
   "          ...                ......  .:oo,  ",
   "   .;clol:,.                        .loooo' ",
   "  :ooooooooo,                        'ooool ",
   "'ooooooooooo.                        loooo.",
   "'ooooooooool                         coooo.",
   " ,loooooooc.                        .loooo.",
   "   .,;;;'.                          ;ooooc  ",
   "       ...                         ,ooool.",
   "    .cooooc.              ..',,'.  .cooo. ",
   "      ;ooooo:.           ;oooooooc.  :l. ",
   "       .coooooc,..      coooooooooo. ",
   "         .:ooooooolc:. .ooooooooooo' ",
   "           .':loooooo;  ,oooooooooc ",
   "               ..';::c'  .;loooo:' ",
      NULL
   };

   return art;
}

char **gentoo_ascii(void)
{
   static char *art[] = 
   {
   "            -/oyddmdhs+:.                ",
   "        -odNMMMMMMMMNNmhy+-`             ",
   "      -yNMMMMMMMMMMMNNNmmdhy+-           ",
   "    `omMMMMMMMMMMMMNmdmmmmddhhy/`        ",
   "    omMMMMMMMMMMMNhhyyyohmdddhhhdo`      ",
   "   .ydMMMMMMMMMMdhs++so/smdddhhhhdm+`    ",
   "    oyhdmNMMMMMMMNdyooydmddddhhhhyhNd.   ",
   "     :oyhhdNNMMMMMMMNNNmmdddhhhhhyymMh   ",
   "       .:+sydNMMMMMNNNmmmdddhhhhhhmMmy   ",
   "          /mMMMMMMNNNmmmdddhhhhhmMNhs:   ",
   "       `oNMMMMMMMNNNmmmddddhhdmMNhs+`    ",
   "     `sNMMMMMMMMNNNmmmdddddmNMmhs/.      ",
   "    /NMMMMMMMMNNNNmmmdddmNMNdso:`        ",
   "   +MMMMMMMNNNNNmmmmdmNMNdso/-           ",
   "   yMMNNNNNNNmmmmmNNMmhs+/-`             ",
   "   /hMMNNNNNNNNMNdhs++/-`                ",
   "   `/ohdmmddhys+++/:.`                   ",
   "     `-//////:--.                        ",
      NULL
   };

  return art;
}

char **unsupported_ascii(void)
{
   static char *art[] =
   { 
   "         <My distro is doesn't             ",
   "          have an ASCII :( > ",
   "   ___        /      ",
   "   (.. \\    /       ",
   "   (<> |            ",
   "  //  \\ \\         ",
   " ( |  | /|          ",
   "_/\\ __)/_)         ",
   "\\/-____\\/         ",
      NULL
   };

   return art;
}


