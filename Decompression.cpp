#include <iostream>
#include <stdio.h>
#include <fstream> 
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
	char x[100000];
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
	void DispAll(ofstream &f2)
	{
		CNode *pTrav;
		pTrav=pHead;
		char ch;
		int i;
		while(pTrav!=NULL)
		{
			ch= pTrav->letter;
			f2.write ( &ch , 1);
			for(i=0; pTrav->x[i]!=NULL; i++)
			{
				ch= pTrav->x[i];
				f2.write ( &ch , 1);
			}
			ch= ' ';
			f2.write ( &ch , 1);
			/*cout<<pTrav->freq<<" ";
			cout<<pTrav->ct<<" ";
			cout<<pTrav->x<<endl;*/
			pTrav=pTrav->pnext;
		}
		ch=';';
		f2.write ( &ch , 1);
		ch='$';
		f2.write ( &ch , 1);
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
	ifstream   f1 ("compressed.txt", ifstream::binary);
	ofstream   f2 ("decompressed.txt", ofstream::binary);
	int j,Num;
	f1.seekg (0, f1.end);
	Num = f1.tellg();
	f1.seekg (0, f1.beg);
	char y[200000];
	char ch;
	for(j=0; j<Num; j++)
	{
		f1.read ( &ch , 1);
		y[j]=ch;
	}
	//cout<<y[j];
	int  l=y[0]-'0';
	//cout<<Num;
	for(j=0;j<Num;j++)
	{
		if(y[j]==';'&&y[j+1]=='$')
		{
			//cout<<y[j]<<y[j+1];
			break;
		}
	}
	CList HL;
	CNode *pnn;
	int num=j;
	int i;
	for(j=1; j<num; )
	{
		i=0;
		pnn= new CNode;
		pnn->letter=y[j];
		j++;
		while(y[j]=='0'||y[j]=='1')
		{
			pnn->x[i]=y[j];
			i++;
			j++;
		}
		j++;
		pnn->x[i]=NULL;
		pnn->pRight=NULL;
		pnn->pLeft=NULL;
		pnn->freq=0;
		pnn->ct=0;
		pnn->pnext=NULL;
		HL.Attach(pnn);
	}
	j+=2;

	CNode *pTrav;
	pTrav=HL.pHead;
	while(pTrav!=NULL)
	{
		cout<<pTrav->letter;
		cout<<pTrav->x;
		pTrav=pTrav->pnext;
	}
	char d[200000];
	int ct,N,c=0,t=0;
	char m=1,z;
	int F,k;
	m=1;
	char R=0;
	char Tmp[200000];
	for( ;j<Num; j++)
	{
		z=y[j];
		for(i=7;i>-1;i--)
		{
			/*if(j==Num+1 && i==l+1 )
			{
				cout<<Tmp;
				break;
			}*/
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
				//cout<<ct<<N;
				if(ct==N )
				{
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
	int n=c;
	for(c=0;c<n;c++)
	{
		ch=d[c];
		f2.write ( &ch , 1);
	}
	system("pause");
}