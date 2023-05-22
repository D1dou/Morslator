#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

void on_file_operation_button_clicked(GtkWidget *widget, gpointer data) {
  int operation_index = GPOINTER_TO_INT(data);

  static const char *operations[] = {"AES/encrypt/encrypt_aes", "AES/decrypt/decrypt_aes", "RSA/encrypt/encrypt_rsa", "RSA/decrypt/decrypt_rsa", "morse_translator/to_text/text_to_morse", "morse_translator/to_morse/text_to_morse"};

  if (operation_index >= 0 && operation_index < sizeof(operations) / sizeof(operations[0])) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint response;

    dialog = gtk_file_chooser_dialog_new("Choose a .txt file", NULL, action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

    response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_ACCEPT) {
      char *filename;
      GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
      filename = gtk_file_chooser_get_filename(chooser);

      gchar *command = g_strdup_printf("./%s %s", operations[operation_index], filename);
      g_print("Executing: %s\n", command);
      system(command);
      g_free(command);
      g_free(filename);
    }

    gtk_widget_destroy(dialog);
  } else {
    g_print("Invalid operation index: %d\n", operation_index);
  }
}

void on_encryption_method_button_clicked(GtkWidget *widget, gpointer data) {
  char *method = (char *)data;

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button1, *button2;

  static const char *operations[] = {"encrypt_aes", "decrypt_aes", "encrypt_rsa", "decrypt_rsa"};

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), method);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  button1 = gtk_button_new_with_label("Encrypt");
  gtk_widget_set_size_request(button1, 120, 50);
  int operation_index = (strcmp(method, "AES") == 0) ? 0 : 2;
  g_signal_connect(button1, "clicked", G_CALLBACK(on_file_operation_button_clicked), GINT_TO_POINTER(operation_index));

  button2 = gtk_button_new_with_label("Decrypt");
  gtk_widget_set_size_request(button2, 120, 50);
  operation_index++;
  g_signal_connect(button2, "clicked", G_CALLBACK(on_file_operation_button_clicked), GINT_TO_POINTER(operation_index));

  gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button2, 0, 1, 1, 1);

  gtk_widget_set_halign(button1, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(button2, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button1, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button2, GTK_ALIGN_CENTER);

  gtk_widget_show_all(window);
}

void on_file_type_button_clicked(GtkWidget *widget, gpointer data) {
  char *file_type = (char *)data;

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button1, *button2, *button3, *button4; // Add button4 
  
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint response;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), file_type);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  if (g_strcmp0(file_type, "txt") == 0) {
    button1 = gtk_button_new_with_label("AES");
    gtk_widget_set_size_request(button1, 120, 50);
    g_signal_connect(button1, "clicked", G_CALLBACK(on_encryption_method_button_clicked), (gpointer) "AES");

    button2 = gtk_button_new_with_label("RSA");
    gtk_widget_set_size_request(button2, 120, 50);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_encryption_method_button_clicked), (gpointer) "RSA");

    button3 = gtk_button_new_with_label("Morse");
    gtk_widget_set_size_request(button3, 120, 50);
    g_signal_connect(button3, "clicked", G_CALLBACK(on_encryption_method_button_clicked), (gpointer) "Morse");

    // Adding blowfish button
    button4 = gtk_button_new_with_label("Blowfish");
    gtk_widget_set_size_request(button4, 120, 50);
    g_signal_connect(button4, "clicked", G_CALLBACK(on_encryption_method_button_clicked), (gpointer) "Blowfish");

    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button4, 0, 3, 1, 1); // Grid attach for button4
  }
  
  if (g_strcmp0(file_type, "wav") == 0) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint response;

    dialog = gtk_file_chooser_dialog_new("Choose a .wav file", NULL, action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

    response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);

        if(filename) {
            gchar *command = g_strdup_printf("./analyse/analyse %s", filename);
            if(command) {
                system(command);
                g_free(command);
            }
            g_free(filename);
        }
    }
    gtk_widget_destroy(dialog);
}
  
  
  gtk_widget_set_halign(button1, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(button2, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button1, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button2, GTK_ALIGN_CENTER);

  if (button3) {
    gtk_widget_set_halign(button3, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button3, GTK_ALIGN_CENTER);
  }

  // Setting alignment for button4
  if (button4) {
    gtk_widget_set_halign(button4, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button4, GTK_ALIGN_CENTER);
  }

  gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button1, *button2;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Choose a file type");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  button1 = gtk_button_new_with_label(".txt file");
  gtk_widget_set_size_request(button1, 120, 50);
  g_signal_connect(button1, "clicked", G_CALLBACK(on_file_type_button_clicked), (gpointer) "txt");

  button2 = gtk_button_new_with_label(".wav file");
  gtk_widget_set_size_request(button2, 120, 50);
  g_signal_connect(button2, "clicked", G_CALLBACK(on_file_type_button_clicked), (gpointer) "wav");

  gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button2, 0, 1, 1, 1);

  gtk_widget_set_halign(button1, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(button2, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button1, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button2, GTK_ALIGN_CENTER);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
