
#include <stdio.h>
#include <string.h>


typedef enum order_table_enum{TFTP_PUT=0,TFTP_GET,TFTP_LIST,TFTP_HELP,TFTP_QUIT,WRONG}order_table_enum_t;// number table
char *order_table_string[]={"put","get","list","help","quit",NULL};

typedef struct order_s {
  char buff[1024];//整个命令
  int table[10];//每个参数的下标号码
  enum order_table_enum order_n;//命令编号
}ORDER_S;


order_table_enum_t get_order(ORDER_S*order_s);


void process(ORDER_S*order_s);
void put_process(const ORDER_S*order_s);
void get_process(const ORDER_S*order_s);
void list_process(const ORDER_S*order_s);
void help_process(void);
void quit_process(const ORDER_S*order_s);
void wrong_processs(const ORDER_S*order_s);


int main(int argc, const char *argv[])
{

  ORDER_S order_s;
  while(1)
  {
    get_order(&order_s);
    process(&order_s);
  }

  return 0;
}


//填充填充order_s结构体
order_table_enum_t get_order(ORDER_S*order_s)
{
  char *p1,*p2;

  printf("<zhaohe>#:");
  fgets(order_s->buff,sizeof(order_s->buff),stdin);
  order_s->buff[strlen(order_s->buff)-1]='\0';

  //strtok 分解字符串  填写order_s->table[]
  int i=1;
  p1=strtok(order_s->buff," ");
  order_s->table[0]=0;
  while( (p2=strtok(NULL," ")) != NULL)
  {
    order_s->table[i]=p2-p1;
    i++;
  }

  //填写结构体的order_s->order_n
  for (int j = 0; order_table_string[j]!=NULL; ++j)
  {
    if (strcmp(order_table_string[j],&order_s->buff[0])==0)
    {
      order_s->order_n=(order_table_enum_t)j; //填写对应的指令编号
      break;
    }
    else if(order_table_string[j+1]==NULL)
    {
      order_s->order_n=(order_table_enum_t)(j+1);//如果所有命令都不匹配填写WRONG
    }
  }

  // printf("调试信息：命令是%s%lu\n", order_s->buff,sizeof(order_s->buff));
  return order_s->order_n;
}

void process(ORDER_S*order_s)
{
  switch(order_s->order_n)
  {
    case TFTP_PUT:  put_process(order_s); break;
    case TFTP_GET:  get_process(order_s);break;
    case TFTP_LIST: list_process(order_s); break;
    case TFTP_HELP: help_process(); break;
    case TFTP_QUIT: quit_process(order_s);break;
    case WRONG: wrong_processs(order_s); break;
    default:printf("switch wrong :遇到未知值\n"); break;
  }
}


void put_process(const ORDER_S*order_s)
{
  printf("put_process........\n");
  return;
}

void get_process(const ORDER_S*order_s)
{
  printf("get_process........\n");
  return;
}


void list_process(const ORDER_S*order_s)
{
  printf("list_process........\n");
  return;
}


void quit_process(const ORDER_S*order_s)
{
  printf("quit_process.......\n");
  return;
}

void help_process(void)
{
  printf("****************************************\n");
  printf("*put <file name>                       *\n");
  printf("*get <file name>                       *\n");
  printf("*list <dir name>                       *\n");
  printf("*quit                                  *\n");
  printf("****************************************\n");
  return;
}

void wrong_processs(const ORDER_S*order_s)
{
  printf("wrong_process.......\n");
  return;
}












