#include <iostream>
#include <stdio.h>
using namespace std;
class CNode
{
public:
	char letter;
	int freq;
	int ct;
	CNode* pnext;
	CNode *pLeft;
	CNode *pRight;
	char x[100];
};
class CList
{
public:
	CNode* pHead;
	CNode* pTail;
	CList()
	{
		pHead= NULL;
		pTail= NULL;
	}
	void Attach(CNode * pnn)
	{
		if(pHead== NULL)
		{
			pHead=pTail=pnn;
		}
		else
		{
			pTail->pnext=pnn;
			pTail=pnn;
		}
	}
	void DispAll()
	{
		CNode *pTrav;
		pTrav=pHead;
		while(pTrav!=NULL)
		{
			cout<<pTrav->letter<<" ";
			/*cout<<pTrav->freq<<" ";
			cout<<pTrav->ct<<" ";*/
			cout<<pTrav->x<<endl;
			pTrav=pTrav->pnext;
		}
	}
};
class CSList
{
public:
	CNode* pHead;
	CSList()
	{
		pHead= NULL;
	}
	void Insert( CNode* pnn)
	{
		CNode *pB=NULL;
		CNode *pTrav=pHead;
		while(pTrav!=NULL)
		{
			if(pTrav->freq>pnn->freq)
			{
				break;
			}
			pB=pTrav;
			pTrav=pTrav->pnext;
		}
		if(pB!=NULL)
		{
			pB->pnext=pnn;
		}
		else
		{
			pHead=pnn;
		}
		pnn->pnext=pTrav;
	}
	CNode* pop()
	{
		if(pHead==NULL)
		{
			return pHead;
		}
		else
		{
			CNode *pTrav=pHead;
			pHead=pHead->pnext;
			pTrav->pnext=NULL;
			return pTrav;
		}
	}
	
	void CopyHuff( CNode *pTrav, CList &HL)
	{
		if(pTrav==NULL)
		{
			return;
		}
		CopyHuff(pTrav->pLeft, HL);
		if(pTrav->pLeft==NULL&&pTrav->pRight==NULL)
		{
			CNode *pnn= new CNode;
			pnn->letter=pTrav->letter;
			pnn->freq=pTrav->freq;
			pnn->ct=0;
			pnn->pLeft=NULL;
			pnn->pnext=NULL;
			pnn->pRight=NULL;
			int i;
			for(i=0; pTrav->x[i]!=NULL; i++)
			{
				pnn->x[i]=pTrav->x[i];
			}
			pnn->x[i]=NULL;
			HL.Attach(pnn);
		}
		CopyHuff(pTrav->pRight, HL);
	}
	void Huffmancode(CNode* pTrav, int i)
	{
		
		if(pTrav->pLeft==NULL&&pTrav->pRight==NULL)
		{
			return;
		}
	
		for(i=0;pTrav->x[i]!='\0';i++)
		{
			pTrav->pLeft->x[i]=pTrav->x[i];
		}
		pTrav->pLeft->x[i]='0';
		pTrav->pLeft->x[i+1]=NULL;
		i=0;
		Huffmancode(pTrav->pLeft,i);
		for(i=0;pTrav->x[i]!='\0';i++)
		{
			pTrav->pRight->x[i]=pTrav->x[i];
		}
		pTrav->pRight->x[i]='1';
		pTrav->pRight->x[i+1]=NULL;
		i=0;
		
		Huffmancode(pTrav->pRight,i);
	}
	/*void Disp2()
	{
		CNode *pTrav;
		pTrav=pHead;
		while(pTrav!=NULL)
		{
			cout<<pTrav->letter<<" "<<pTrav->freq<<endl;
			pTrav=pTrav->pnext;
		}
	}*/
};

void main()
{
	int i,F;
	char x[20000];
	gets (x);
	CList L;
	CNode *pTrav;
	CNode *pnn;
	for(i=0; x[i]!=NULL ;i++)
	{
		F=1;
		pTrav=L.pHead;
		while(pTrav!=NULL)
		{
			if(x[i]==pTrav->letter)
			{
				F=0;
				break;
			}
			pTrav=pTrav->pnext;
		}
		if(F==0)
		{
			pTrav->freq++;
		}
		else
		{
			pnn= new CNode;
			pnn->letter=x[i];
			pnn->freq=1;
			pnn->ct=0;
			pnn->pnext=NULL;
			pnn->pRight=NULL;
			pnn->pLeft=NULL;
			pnn->x[0]=NULL;
			L.Attach(pnn);
		}
	}
	CSList SortedL;
	pTrav=L.pHead;
	while(pTrav!=NULL)
	{
		pnn= new CNode;
		pnn->letter=pTrav->letter;
		pnn->freq=pTrav->freq;
		pnn->ct=0;
		pnn->pnext=NULL;
		pnn->pRight=NULL;
		pnn->pLeft=NULL;
		pnn->x[0]=NULL;
		SortedL.Insert(pnn);
		pTrav=pTrav->pnext;
	}

	//SortedL.Disp2();

	CNode *pNew;
	CNode *pTrav1;
	CNode *pTrav2;
	
	while(SortedL.pHead->pnext!=NULL)
	{
		pNew= new CNode;
		pTrav1= SortedL.pop();
		pNew->pLeft= pTrav1;
		pTrav2= SortedL.pop();
		pNew->pRight= pTrav2;
		pNew->freq= pTrav1->freq + pTrav2->freq;
		pnn->ct=0;
		pNew->letter=NULL;
		pNew->pnext=NULL;
		pNew->x[0]=NULL;
		SortedL.Insert(pNew);
	}

	
	pTrav=SortedL.pHead;
	i=0;
	pTrav->x[0]=NULL;
	SortedL.Huffmancode(pTrav,i);
	pTrav=SortedL.pHead;
	CList HL;
	SortedL.CopyHuff(pTrav, HL);
	HL.DispAll();

	char m=1,z=0;
	int s,k,j=0;
	i=7;
	F=0;
	int num=0;
	char y[200000];
	for(s=0;x[s]!=NULL;s++)
	{
		pTrav=HL.pHead;
		while(pTrav->letter!=x[s])
		{
			pTrav=pTrav->pnext;
		}
		for(k=0;pTrav->x[k]!=NULL;k++)
		{
			F=0;
			if(i==-1)
			{
				F=1;
				y[j]=z;
				z=0;
				j++;
				i=7;
				num++;
			}
			//m=pTrav->x[k];
			if(pTrav->x[k]=='1')
			{
				z=z|(m<<i);
			}
			i--;
		}
	}
	if(F==0)
	{
		y[j]=z;
		z=0;
		j++;
		num++;
	}
	y[j]=NULL;
	cout<<"Compressed array"<<endl<<y<<endl;
	char d[200000];
	int ct,N,c=0,t=0;
	m=1;
	char R=0;
	char Tmp[200000];
	for(j=0;j<=num;j++)
	{
		z=y[j];
		for(i=7;i>=0;i--)
		{
			pTrav=HL.pHead;
			F=1;
			while(pTrav!=NULL)
			{
				if(pTrav->ct!=pTrav->freq)
				{
					F=0;
				}
				pTrav=pTrav->pnext;
			}
			if(F==1)
			{
				break;
			}
			R=z&(m<<i);
			if(R!=0)
			{
				Tmp[t]='1';
				t++;
			}
			else
			{
				Tmp[t]='0';
				t++;
			}
			Tmp[t]=NULL;
			pTrav=HL.pHead;
			while(pTrav!=NULL)
			{
				N=0;
				ct=0;
				for(k=0;pTrav->x[k]!=NULL;k++)
				{
					N++;
				}
				for(k=0;pTrav->x[k]!=NULL&&Tmp[k]!=NULL;k++)
				{
					if(pTrav->x[k]==Tmp[k])
					{
						ct++;
					}
				}
				if(ct==N)
				{
					pTrav->ct++;
					d[c]=pTrav->letter;
					c++;
					R=0;
					Tmp[0]=NULL;
					t=0;
					break;
				}
				
				pTrav=pTrav->pnext;
			}
		}
	}
	d[c]=NULL;
	cout<<"Decompressed array"<<endl<<d<<endl;
	system("pause");
}