////////////////// Student database application using Linked-List //////////////

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct db
{
	int roll;
	char name[20];
	float marks;
	struct db *next;
};

void print(struct db *p);
void save(struct db *p);
void add_record(struct db **head);
void read_from_file(struct db **head);
void del_record(struct db **head);
main()
{
	struct db *head=NULL;
	char ch,a,p,d,q;
	read_from_file(&head);
	while(1)
	{
		printf("********MENU*******\n");
		printf(" A:Add record\n D:Delete record\n P:Print record\n S:Save record\n Q:Quit \n");
		printf("enter your choice\n");
		scanf(" %c",&ch);

		switch(ch)
		{
			case 'a':
			case 'A':add_record(&head); 
				 break;
			case 'd':
			case 'D':del_record(&head);
				 break;
			case 'p':
			case 'P':print(head);
				 break;
			case 's':
			case 'S':save(head);
				 break;
			case 'q':
			case 'Q':return 0; 
				 break;
			default : printf("Invalid choice\n");
		}
	}
}
//////////////////      ADD  new record     //////////////////////////////
void add_record(struct db **head)
{ 
	int ch;
	struct db *nu,*temp,*pre;
	nu=malloc(sizeof(struct db));
	printf("enter roll no\n");
	scanf("%d",&(nu->roll));
	printf("enter marks\n");
	scanf("%f",&(nu->marks));
	printf("enter name\n");
	getchar();
	scanf("%s",(nu->name));

	if(*head==NULL)
	{
		nu->next=NULL;
		*head=nu;
	}
	else
	{
		if((nu->roll)<((*head)->roll))
		{
			nu->next=*head;
			*head=nu;
		}
		else

		{
			temp=*head;
			///////////////   using pre pointer which preceds temp    /////////////////////

			/*  while(temp && (temp->roll < nu->roll))
			    {
			    pre=temp;
			    temp=temp->next;
			    }
			    nu->next=pre->next;
			    pre->next=nu;*/

			while((temp->next)&&(temp->next->roll < nu->roll))
				temp=temp->next;
			nu->next=temp->next;
			temp->next=nu;

		}
	}   
}    
////////////////////     PRINT all record   //////////////////////////////
void print(struct db *p)
{
	if(p==NULL)
	{
		printf("NO DATA...<enter data to print>\n");
		return;
	}
	while(p)
	{
		printf("%d %s %.2f\n",p->roll,p->name,p->marks);
		p=p->next;
	}
	// return;
}
///////////////////   DELETE record (all OR selective)    ///////////////////
void del_record(struct db **head)
{
	struct db *temp,*pre;      
	int rolltodel;
	char ch;
	printf("you want to delete all data or selective data:(Y/N)\n");
	scanf(" %c",&ch);

	if(ch=='y')
	{
		while((*head))
		{
			temp=(*head);
			(*head)=(*head)->next;
			free(temp);
		}
	}
	else
	{
		printf("Enter roll no. which you want to delet:\n");
		scanf("%d",&rolltodel); 
		for(temp=(*head);temp;pre=temp,temp=temp->next) 
		{
			if(temp->roll==rolltodel)
				break;
		} 
		if(temp==NULL)
		{
			printf("entered roll no not found\n");
			return;
		}
		if(temp==(*head))
		{
			(*head)=(*head)->next;
			free(temp);
		}
		else
		{
			pre->next=temp->next;
			free(temp);
		}
	}
}
////////////////      SAVE all data to the file     //////////////////
void save(struct db *head)
{
	FILE *fp;

	fp=fopen("database","w");
	while(head)
	{
		fwrite(head,(sizeof(struct db)-sizeof(struct db *)),1,fp);
		head=head->next;
	}
	fclose(fp);
}
/////////////////    READ  data from the file      ///////////////////////
void read_from_file(struct db ** head)
{
	FILE *fp;
	struct db *nu,*last,v;
	fp=fopen("database","r");

	if(fp==NULL)
		return;

	while(fread(&v,(sizeof(struct db)-sizeof(struct db *)),1,fp)==1)
	{
		nu=malloc(sizeof(struct db));
		memcpy(nu,&v,(sizeof(struct db)-sizeof(struct db *)));
		nu->next=0;
		if((*head)==0)
		{
			(*head)=nu;
			last=nu;
		}
		else
		{
			last->next=nu;
			last=nu;
		}
	}
	fclose(fp);
}
