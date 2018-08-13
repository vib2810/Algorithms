#include<stdio.h>
#include<stdlib.h>
/*------------------------------------------Definifion of Structure---------------------------------------------------*/
typedef struct node //Structure to store a point in 2d
{
	int    index; // i corresponding to xi
 	float  coeff; // ai or bi or ... (may be negative)
  	struct node *next;
} node;
typedef struct node2
{
	node *a;
	node *b;
} node2;
/*------------------------------------------End of Definifion of Structure--------------------------------------------*/

/*------------------------------------------Definifion of Functions---------------------------------------------------*/
void monoinserte(node **head, node mono) //Inserts the node mono to the end of the list *head
{
	node *temp=(node *)malloc(sizeof(node));
	temp->index=mono.index;
	temp->coeff=mono.coeff;
	temp->next=NULL;
	
	node *t=*head;
	if(t==NULL)
	{
		*head=temp;	
		return;
	}
	while(t->next!=NULL) 
	{
		t=t->next;
	}
	t->next=temp;
	return;
}


void monoinserts(node **head, node mono) //Inserts the node mono to the start of the list *head
{
	node *temp=(node *)malloc(sizeof(node));
	temp->index=mono.index;
	temp->coeff=mono.coeff;
	temp->next=*head;
	*head=temp;
	return;
}


void polydisp(node *head)  //Print the polynomial
{
	node *t=head;
	while(t!=NULL)
	{
		printf("%fx^%d ", t->coeff, t->index);
		t=t->next;
		if(t!=NULL) printf("+");
	}
	printf("\n");
	return;
}

node *polyadd(node *p1, node *p2) //Adds p1 and p2, Returns pointer to their sum
{
	node *t1=p1;
	node *t2=p2;
	
	node temp;
	node *anshead=NULL;
	
	while(t1!=NULL && t2!=NULL)
	{
		temp.next=NULL;
		if(t1->index == t2->index) 
		{
			temp.coeff= (t1->coeff) + (t2->coeff);
			temp.index= (t1->index);
			monoinserte(&anshead,temp);
			t1=t1->next;
			t2=t2->next;
		}
		else if(t1->index > t2->index) 
		{
			temp.coeff= (t1->coeff);
			temp.index= (t1->index);
			monoinserte(&anshead,temp);
			t1=t1->next;
		}
		else if(t1->index < t2->index) 
		{
			temp.coeff= (t2->coeff);
			temp.index= (t2->index);
			monoinserte(&anshead,temp);
			t2=t2->next;
		}
	}
	if(t2!=NULL)
	{
		while(t2!=NULL)
		{
			temp.coeff= (t2->coeff);
			temp.index= (t2->index);
			monoinserte(&anshead,temp);
			t2=t2->next;
		}
	}
	if(t1!=NULL)
	{
		while(t1!=NULL)
		{
			temp.coeff= (t1->coeff);
			temp.index= (t1->index);
			monoinserte(&anshead,temp);
			t1=t1->next;
		}
	}
	return anshead;
}

node *polysub(node *p1, node *p2) //Adds p1 and p2, Returns pointer to their sum
{
	node *t1=p1;
	node *t2=p2;
	
	node temp;
	node *anshead=NULL;
	
	while(t1!=NULL && t2!=NULL)
	{
		temp.next=NULL;
		if(t1->index == t2->index) 
		{
			temp.coeff= (t1->coeff) - (t2->coeff);
			temp.index= (t1->index);
			monoinserte(&anshead,temp);
			t1=t1->next;
			t2=t2->next;
		}
		else if(t1->index > t2->index) 
		{
			temp.coeff= (t1->coeff);
			temp.index= (t1->index);
			monoinserte(&anshead,temp);
			t1=t1->next;
		}
		else if(t1->index < t2->index) 
		{
			temp.coeff= -(t2->coeff);
			temp.index= (t2->index);
			monoinserte(&anshead,temp);
			t2=t2->next;
		}
}
	if(t2!=NULL)
	{
		while(t2!=NULL)
		{
			temp.coeff= -(t2->coeff);
			temp.index= (t2->index);
			monoinserte(&anshead,temp);
			t2=t2->next;
		}
	}
	if(t1!=NULL)
	{
		while(t1!=NULL)
		{
			temp.coeff= (t1->coeff);
			temp.index= (t1->index);
			monoinserte(&anshead,temp);
			t1=t1->next;
		}
	}
	
	return anshead;
}
void delnode(node **p,node *d)
{
	if(d==*p)
	{
		free(*p);
		*p=(*p)->next;
	}
	else
	{
		node *t1=(*p)->next;
		node *t2=*p;
		while(t1!=d && t1!=NULL)
		{
			t1=t1->next;
			t2=t2->next;
		}
		t2->next=t1->next;
		free(t1);
	}
}
void opt(node **p)
{
	node *t=*p;
	while(t!=NULL)
	{
		if(t->coeff==0 && t->index!=0) delnode(p,t);
		t=t->next;
	}
	return;
}
int mono(node *p)
{
	int count=0;
	node *t=p;
	while(t!=NULL)
	{
		if(t->coeff!=0) count ++;
		t=t->next;
	}
	if(count==1) return 1;
	return 0;
}
int max(int a,int b)
{
	if(a>b) return a;
	return b;
}
/*------------------------------------------End of Definifion of functions---------------------------------------------*/

/*------------------------------------------Multiplication by recursion------------------------------------------------*/
node * monomul (node *p, node m) //Multiply a node with a polynomial, return pointer to answer list
{
	node *t=p;
	node temp;
	node *anshead=NULL;
	while(t!=NULL)
	{
		temp.coeff= (t->coeff) * (m.coeff);
		temp.index= (t->index) + (m.index);
		monoinserte(&anshead,temp);
		t=t->next;
	}
	return anshead;
}

node *mul(node *p1,node *p2) //Recursively Term by Term multiply p1 and p2
{
	node *anshead=NULL;
	if(mono(p2)==1) 
	{
		node temp;
		temp.coeff=p2->coeff;
		temp.index=p2->index;
		anshead=monomul(p1,temp);
		return anshead;
	}
	else
	{ 
		return polyadd(  monomul(p1,*p2) , mul(p1,p2->next)  );
	}
}
/*------------------------------------------End of Multiplication by recursion------------------------ ----------------*/

/*------------------------------------------Karatsuba functions--------------------------------------------------------*/
//Karatsuba functions
//Decomposes p about n=degree/2. Stores the decomposed polynomials in node2 *d. Returns pointer to node2 
node2 *decomp(node *p,int n)  
{
	node2 *d=(node2 *)malloc(sizeof(node2));
	node *t=p;
	node temp;
	d->a=NULL;
	d->b=NULL;
	if(p->index < n)
	{
		temp.coeff   =0;
		temp.index   =0;
		monoinserte(&(d->a),temp);
		d->b=p;
		return d;
	}
	while(t->index >= n) 
	{
		temp.coeff   =t->coeff;
		temp.index  =t->index -n;
		monoinserte(&(d->a),temp);
		t=t->next;
	}
	while(t!=NULL)
	{
		temp.coeff   =t->coeff;
		temp.index  =t->index;
		monoinserte(&(d->b),temp);
		t=t->next;
	}
	if(d->a==NULL) 
	{
		temp.coeff   =0;
		temp.index   =0;
		monoinserte(&(d->a),temp);
	}
	if(d->b==NULL) 
	{
		temp.coeff   =0;
		temp.index   =0;
		monoinserte(&(d->b),temp);
	}
	return d;
}
//Recursive karatsuba multiplication
node *karatmul(node *p1,node *p2)
{
	if(mono(p1)==1)
	{
		node n1;
		n1.coeff=p1->coeff;
		n1.index=p1->index;
		return monomul(p2,n1);
	}
	//p2 is monomial
	if(mono(p2)==1)
	{
		node n2;
		n2.coeff=p2->coeff;
		n2.index=p2->index;
		return monomul(p1,n2);
	}
	//Recursive call
	node2 *d1,*d2;
	int n=max(p1->index,p2->index)/2;
	if(n==0) n=1;
	d1=decomp(p1,n);
	d2=decomp(p2,n);
	node *r0=karatmul(d1->b,d2->b);
	node *r1=karatmul( polyadd(d1->a,d1->b),  polyadd(d2->a,d2->b) ) ;
	node *r2=karatmul(d1->a,d2->a);
	node *ans, *ans1;
	
	node xm2,xm;
	xm2.coeff=1;
	xm2.index=2*n;
	xm.coeff=1;
	xm.index=n;
	
	ans=polyadd( r0, monomul(r2,xm2));
	ans1=polyadd( r0, r2);
	ans1=polysub( r1, ans1);
	ans1=monomul(ans1,xm);
	ans=polyadd(ans,ans1);
	return ans;
}



int main1()
{
	//Definition of structures
	int i1,i2,i,flag=0;
	node temp;
	node *p1=NULL, *p2=NULL, *p=NULL;
	
	//Get polynomial 1
	printf("Enter the index of the first polynomial\n");
	scanf("%d",&i1);
	for(i=0;i<i1+1;i++)
	{
		printf("\nEnter the coefficient of x^%d: ",i);
		scanf("%f",&temp.coeff);
		temp.index=i;
		monoinserts(&p1,temp);
	}
	
	//Get polynomial 2
	printf("Enter the index of the second polynomial\n");
	scanf("%d",&i2);
	for(i=0;i<i2+1;i++)
	{
		printf("\nEnter the coefficient of x^%d: ",i);
		scanf("%f",&temp.coeff);
		temp.index=i;
		monoinserts(&p2,temp);
	}
	
	opt(&p1);
	opt(&p2);
	
	//Display the scanned polynomials
	printf("\nThe polynomial 1 is :");
	polydisp(p1);
	printf("\nThe polynomial 2 is :");
	polydisp(p2);
	printf("\n");
	
	//Add p1 and p2
	p=polyadd(p1,p2);
	
	//Check is all coefficients are 0, replace with a monomial 0.000000x^0
	node *t=p;
	while(t!=NULL) //flag is 1 if even one entry is non 0
	{
		if( t->coeff != 0 ) flag=1;
		t=t->next;
	}
	if(flag==0)    //If all are 0, free all nodes of p, append the monmomial 0.000000x^0 to p
	{
		t=p;
		while(t!=NULL)
		{
			free(t);
			t=t->next;
		}
		p=NULL;
		temp.coeff=0;
		temp.index=0;
		monoinserts(&p,temp);
	}
	
	//Print results
	printf("The sum of the polynomials is: ");
	polydisp(p);
	return 0;		
}				
					
						
							
int main2()
{
	//Definition of structures
	int i1,i2,i,flag=0;
	node temp;
	node *p1=NULL, *p2=NULL, *p=NULL;
	
	//Get polynomial 1
	printf("Enter the index of the first polynomial\n");
	scanf("%d",&i1);
	for(i=0;i<i1+1;i++)
	{
		printf("\nEnter the coefficient of x^%d: ",i);
		scanf("%f",&temp.coeff);
		temp.index=i;
		monoinserts(&p1,temp);
	}
	
	//Get polynomial 2
	printf("Enter the index of the second polynomial\n");
	scanf("%d",&i2);
	for(i=0;i<i2+1;i++)
	{
		printf("\nEnter the coefficient of x^%d: ",i);
		scanf("%f",&temp.coeff);
		temp.index=i;
		monoinserts(&p2,temp);
	}

	opt(&p1);
	opt(&p2);
	//Display the scanned polynomials
	printf("\nThe polynomial 1 is :");
	polydisp(p1);
	printf("\nThe polynomial 2 is :");
	polydisp(p2);
	printf("\n");
	
	//Multiply p1 and p2
	p=mul(p1,p2);
	
	//Check is all coefficients are 0, replace with a monomial 0.000000x^0
	node *t=p;
	while(t!=NULL) //flag is 1 if even one entry is non 0
	{
		if( t->coeff != 0 ) flag=1;
		t=t->next;
	}
	if(flag==0)    //If all are 0, free all nodes of p, append the monmomial 0.000000x^0 to p
	{
		t=p;
		while(t!=NULL)
		{
			free(t);
			t=t->next;
		}
		p=NULL;
		temp.coeff=0;
		temp.index=0;
		monoinserts(&p,temp);
	}
	
	//Print results of term by term
	printf("The product of the polynomials by term by term is: ");
	polydisp(p);
	
	//Karatsuba
	p=karatmul(p1,p2);
	//Print results of Karatsuba
	printf("The product of the polynomials by karatsuba is: ");
	polydisp(p);	
	
	return 0;
}									
									
int main()
{
	main1();
	main2();
}										
									
												
													
														
															
																
																	
																		
																			
																				
																					
																						
																							
																								
																									

