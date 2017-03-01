#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <gtk/gtk.h>
#include <glib.h>

time_t times;
gint show_time(gpointer label) {
    times = time(NULL);
    gtk_label_set_text(label,ctime(&times));
    return 1;
}

int main(int argc,char *argv[]) {
    GtkWidget *window_T;
    GtkWidget *label_T;
    GtkWidget *window_C;
    GtkWidget *label_C;
    GtkWidget *window_S;
    GtkWidget *label_S;
    int child1pid,child2pid,child3pid;
    
    if((child1pid = fork()) == -1) {    //创建子进程1
        perror("fork 1 failure!");
        exit(1);
    }

    if(child1pid == 0) {    //子进程1运行代码：实时显示当前时间
        //显示实时时间窗口
        gtk_init(&argc,&argv);
        window_T = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        label_T = gtk_label_new(NULL);
        gtk_container_add(GTK_CONTAINER(window_T),label_T);
        gtk_window_set_title(GTK_WINDOW(window_T),"当前时间");
        gtk_window_set_default_size(GTK_WINDOW(window_T),300,200);
        gtk_window_move(GTK_WINDOW(window_T),100,200);
        g_signal_connect(window_T, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        g_timeout_add(1000,show_time,label_T);
        gtk_widget_show_all(window_T);
        gtk_main();
    }
    else {
        if((child2pid = fork()) == -1) {    //再创建子进程2
            perror("fork 2 failure!");
            exit(1);
        }

        if(child2pid == 0) {    //子进程2运行代码：实时显示CPU利用率
            //显示实时CPU利用率窗口
            gtk_init(&argc,&argv);
            window_C = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            label_C = gtk_label_new("wowowowo");
            gtk_container_add(GTK_CONTAINER(window_C),label_C);
            gtk_window_set_title(GTK_WINDOW(window_C),"实时CPU利用率");
            gtk_window_set_default_size(GTK_WINDOW(window_C),300,200);
            gtk_window_set_position(GTK_WINDOW(window_C),GTK_WIN_POS_CENTER_ALWAYS);
            g_signal_connect(window_C, "destroy", G_CALLBACK(gtk_main_quit), NULL);
            gtk_widget_show_all(window_C);
            gtk_main();
        }
        else {
            if((child3pid = fork()) == -1) {    //再创建子进程3
                perror("fork 3 failure!");
                exit(1);
            }

            if(child3pid == 0) {    //子进程3运行代码：1-100累加求和
                //显示1-100累加求和窗口
                gtk_init(&argc,&argv);
                window_S = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                label_S = gtk_label_new("wowowowo");
                gtk_container_add(GTK_CONTAINER(window_S),label_S);
                gtk_window_set_title(GTK_WINDOW(window_S),"累加求和");
                gtk_window_set_default_size(GTK_WINDOW(window_S),300,200);
                gtk_window_move(GTK_WINDOW(window_S),980,200);
                g_signal_connect(window_S, "destroy", G_CALLBACK(gtk_main_quit), NULL);
                gtk_widget_show_all(window_S);
                gtk_main();
            }
            else {  //父进程代码
                waitpid(child1pid,NULL,0);
                waitpid(child2pid,NULL,0);
                waitpid(child3pid,NULL,0);
                exit(0);
            }
        }
    }
    return 0;
}
