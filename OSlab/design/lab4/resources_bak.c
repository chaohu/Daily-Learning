#include "task4.h"

static int flag = 0;    			//计算CPU使用率时启动程序的标志
static float cpu_used_percent = 0;  //CPU使用率
static long idle,total;

static gint cpuPoints[100];

GtkWidget *cpu_record_drawing_area;
GdkPixmap *cpu_graph;

//第二个页面,显示资源信息
void Creat_Page_Two(GtkWidget *notebook) {
	GtkWidget *vbox_r = gtk_vbox_new(FALSE,5);
	GtkWidget *label_r = gtk_label_new("资源");
	GtkWidget *cpu_record = gtk_frame_new("CPU使用记录");   //CPU使用记录窗口
	gtk_container_set_border_width(GTK_CONTAINER(cpu_record),5);
	gtk_widget_set_size_request(cpu_record,700,200);
	gtk_widget_show(cpu_record);
	gtk_box_pack_start(GTK_BOX(vbox_r),cpu_record,FALSE,FALSE,0);

	cpu_record_drawing_area = gtk_drawing_area_new();
	gtk_drawing_area_size(GTK_DRAWING_AREA(cpu_record_drawing_area),500,180);
	gtk_container_add(GTK_CONTAINER(cpu_record),cpu_record_drawing_area);
	gtk_widget_show(cpu_record_drawing_area);
	g_timeout_add(1000,cpu_record_draw,NULL);
	cpu_record_draw(NULL);


	GtkWidget *label_CPU = gtk_label_new(NULL);
	g_timeout_add(1000,CPU_Refresh,label_CPU);
	gtk_box_pack_start(GTK_BOX(vbox_r),label_CPU,FALSE,FALSE,0);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),vbox_r,label_r);
}



/*
 * CPU利用率计算与显示
 */
gint CPU_Refresh(gpointer label) {
	char temp_cpu[50];
	CPU_UseRate();
	sprintf(temp_cpu,"cpu使用率：%0.1f%%",cpu_used_percent);
    gtk_label_set_text(label,temp_cpu);
	gtk_widget_show(label);
    return TRUE;
}

void CPU_UseRate() {
	long user_t,nice_t,system_t,idle_t,total_t;	//此次读取的数据
	long total_c,idle_c;	//此次数据与上次数据的差
	char cpu_t[10],buffer[71];
	FILE *fp;
	fp = fopen("/proc/stat","r");
	if(fp == NULL) {
		perror("fopen");
		exit(1);
	}
	fgets(buffer,70,fp);
	fclose(fp);
	sscanf(buffer, "%s %ld %ld %ld %ld",cpu_t, &user_t, &nice_t, &system_t, &idle_t);
	
	if(flag == 0) {
		flag = 1;
		idle = idle_t;
		total = user_t + nice_t + system_t + idle_t;
		cpu_used_percent = 0;
	}
	else {
		total_t = user_t + nice_t + system_t + idle_t;
		total_c = total_t - total;
		idle_c = idle_t - idle;
		cpu_used_percent = (100.0 * (total_c - idle_c)) / total_c;
		total = total_t;	//此次数据保存
		idle = idle_t;
	}
}

gint cpu_record_draw(gpointer data) {
	/* 建矩形绘图区 */
	GdkGC *gc_chart_cpu = gdk_gc_new(cpu_record_drawing_area->window);
	/* 背景颜色 */
	GdkColor color;
	color.red = 0xFFFF;
	color.green = 0xFFFF;
	color.blue = 0xFFFF;
	gdk_gc_set_rgb_fg_color(gc_chart_cpu, &color);
	int width, height, curPoint, step;
	gdk_draw_rectangle(cpu_graph, gc_chart_cpu, TRUE, 0, 0,cpu_record_drawing_area->allocation.width, cpu_record_drawing_area->allocation.height);
	width = cpu_record_drawing_area->allocation.width;
	height = cpu_record_drawing_area->allocation.height; 
	curPoint = (int) (cpu_used_percent * (double) height);
	cpuPoints[99] = height - curPoint;
	int i; 
	for (i = 0; i < 99; i++)
	cpuPoints[i] = cpuPoints[i + 1];
	step = width / 99;
	GdkGC *gc = gdk_gc_new(GDK_DRAWABLE(cpu_graph));
	gdk_color_parse("black", &color);
	gdk_gc_set_foreground(gc, &color);
	gdk_gc_set_line_attributes(gc, 1, GDK_LINE_SOLID, GDK_CAP_ROUND,GDK_JOIN_MITER);
	for (i = 99; i >= 1; i--) {
		gdk_draw_line(GDK_DRAWABLE(cpu_graph), gc, i * step, cpuPoints[i], (i - 1) * step, cpuPoints[i - 1]);
	}
	gtk_widget_queue_draw(cpu_record_drawing_area);

	return TRUE;
}




gint show_time(gpointer label) {
	times = time(NULL);
	lmodifytime = localtime(&(times));
	sprintf(buf_time,"%0d月%2d日%02d:%02d:%02d",lmodifytime->tm_mon+1,lmodifytime->tm_mday,lmodifytime->tm_hour,lmodifytime->tm_min,lmodifytime->tm_sec);
	gtk_label_set_text(label,buf_time);
	return 1;
}

