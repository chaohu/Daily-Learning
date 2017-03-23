#include "task4.h"


int main(int argc,char *argv[]){
    gtk_init(&argc,&argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"奥-系统资源监视器");
    gtk_window_set_default_size(GTK_WINDOW(window),800,600);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //创建笔记本控件
    GtkWidget *notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window),notebook);
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook),GTK_POS_TOP);

    //第一个页面,显示进程相关信息
	GtkWidget *table_p = gtk_table_new(10,10,TRUE);
	GtkWidget *scroll_p = gtk_scrolled_window_new(NULL,NULL);
    GtkWidget *label_p = gtk_label_new("进程信息");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),table_p,label_p);
	gtk_widget_show(table_p);

	gchar *colname[6] = {"进程名","PID","PPID","state","Mem(KB)","优先级"};
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_p),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
	gtk_table_attach_defaults(GTK_TABLE(table_p),scroll_p,0,10,0,9);
	clist = gtk_clist_new_with_titles(6,colname);
	gtk_clist_set_column_width(GTK_CLIST(clist), 0, 200);
	gtk_clist_set_column_width(GTK_CLIST(clist), 1, 100);
	gtk_clist_set_column_width(GTK_CLIST(clist), 2, 100);
	gtk_clist_set_column_width(GTK_CLIST(clist), 3, 100);
	gtk_clist_set_column_width(GTK_CLIST(clist), 4, 100);
	gtk_clist_set_column_width(GTK_CLIST(clist), 5, 110);
	
	gtk_container_add(GTK_CONTAINER(scroll_p),clist);
	gtk_widget_show(clist);

    g_timeout_add(20000,get_proc,clist);
    get_proc(clist);


	GtkWidget *vbox_r = gtk_vbox_new(FALSE,5);
	GtkWidget *label_r = gtk_label_new("资源信息");

	//CPU利用率
	GtkWidget *label_CPU = gtk_label_new(NULL);
	g_timeout_add(1000,CPU_Refresh,label_CPU);
	gtk_box_pack_start(GTK_BOX(vbox_r),label_CPU,FALSE,FALSE,0);
	//内存利用率
	GtkWidget *label_MEM = gtk_label_new(NULL);
	g_timeout_add(1000,MEM_Refresh,label_MEM);
	gtk_box_pack_start(GTK_BOX(vbox_r),label_MEM,FALSE,FALSE,0);
	

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),vbox_r,label_r);



    //第三个页面,显示系统信息
    GtkWidget *vbox_f = gtk_vbox_new(FALSE,5);
    GtkWidget *label_f = gtk_label_new("系统信息");
    GtkWidget *label_S= gtk_label_new(NULL);
    GtkWidget *label_T= gtk_label_new(NULL);
    SYS_Refresh(label_S);
    g_timeout_add(1000,show_time,label_T);
	gtk_box_pack_start(GTK_BOX(vbox_f),label_S,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox_f),label_T,FALSE,FALSE,0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),vbox_f,label_f);

    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook),0);

    gtk_widget_show_all(window);
    gtk_main();
}
