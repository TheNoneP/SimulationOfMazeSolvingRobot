#include <iostream>
#include <windows.h>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <conio.h>
using namespace std;
int space[11][20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                   1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
				   1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
				   6,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
				   0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
				   0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
				   0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
				   0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,
				   0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,
				   0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0};
char dir ='L';
short SI=0,SJ=19;
bool front=false;
bool righT=false;
bool lefT=false;
bool goal = false;
int  itr = 1,lC=-1,rC=-1,Con= 10;
int BArray[20]={0};
short parent=1;
int ID=0,preID=0,nexID=1;

class Node{
	public :
	Node *parentPointer=NULL;
	Node *leftChild=NULL;
	Node *middleChild=NULL;
	Node *rightChild=NULL;
	char dirFromParent;
	char dirInMaze;
	int ID;
	int NID;
	bool isDiscovered;
	bool isRoot;
};
Node *root = new Node();
Node *preNode,*targetNode;
string preNodeToCPDir="",CPToTargetDir="";
string preNodeToCPID="",targetNodeToCPID="";
stack<Node*> Q;
void fillSpace(short sI,short eI,short sJ,short eJ)
{
	for(int i=sI;i<=eI;i++)
		for(int j=sJ;j<=eJ;j++)
			space[i][j]=1;
}
void setGoalPos(short row,short col)
{
	space[row][col]=6;
}
void printSpace()
{
	for(int i=0;i<10;i++){
		for(int j=0;j<20;j++){
			cout<<space[i][j]<<" ";
			
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<endl;
	cout<<endl;
}
bool isInSpace()
{
	if((SI<=10 && SI>=0) && (SJ>=0 && SJ<=19))
	return true;
	else return false;
}
void changeDirToLeft()
{
	
		if(dir=='L')
		{
			dir = 'D';
		}
		else if(dir == 'R')
		{
			dir = 'U';
		}
		else if(dir =='U')
		{
			dir = 'L';
		}
		else if(dir =='D')
		{
			dir = 'R';
		}
	
}
void changeDirToRight()
{
	if(dir=='L')
		{
			dir = 'U';
		}
		else if(dir == 'R')
		{
			dir = 'D';
		}
		else if(dir =='U')
		{
			dir = 'R';
		}
		else if(dir =='D')
		{
			dir = 'L';
		}
}
void changeDirDE()
{
		if(dir=='L')
		{
			dir = 'R';
		}
		else if(dir == 'R')
		{
			dir = 'L';
		}
		else if(dir =='U')
		{
			dir = 'D';
		}
		else if(dir =='D')
		{
			dir = 'U';
		}
}
void checkDir(short I,short J)
{
	if(isInSpace()==false)
	{
		if(SI>9)SI=9;
		else if(SI<1)SI=1;
		if(SJ>18)SJ=18;
		else if(SJ<1)SJ=1;
		
	}
	if(dir =='L')
	{
		// check front
		if(J>0){
		if(space[I][J-1]!=0) front = true;
		else front = false;
	}else front = false;
		// check left 
		if(I<10){
		if(space[I+1][J]!=0) lefT = true;
		else lefT = false;
	}else lefT = false;
		// check right
		if(I >0){
		if(space[I-1][J]!=0) righT = true;
		else righT = false;
	}else righT = false;
	
	}
	else if(dir =='R')
	{
		// check front
		if(J<19){
		if(space[I][J+1]!=0) front =true;
		else front = false;
	}else front = false;
		// check left
		if(I>0) {
		if(space[I-1][J]!=0) lefT = true;
		else lefT = false;
	}else lefT = false;
		// check right
		if(I<10){
		if(space[I+1][J]!=0) righT = true;
		else righT = false;
	}else righT = false;
	}
	else if(dir =='U')
	{
		// check front
		if(I>0){
		if(space[I-1][J]!=0) front =true;
		else front= false;
	}else front = false;
		// check left 
		if(J>0){
		if(space[I][J-1]!=0) lefT = true;
		else lefT = false;
	}else lefT = false;
		// check right
		if(J<19){
		if(space[I][J+1]!=0) righT = true;
		else righT = false;
	}else righT = false;
	}
	else if(dir =='D')
	{
		// check front
		if(I<10){
		if(space[I+1][J]!=0) front = true;
		else front= false;
	}else front = false;
		// check left 
		if(J<19){
		if(space[I][J+1]!=0) lefT = true;
		else lefT = false;
	}else lefT = false;
		// check right
		if(J>0){
		if(space[I][J-1]!=0) righT = true;
		else righT = false;
	}else righT = false;
	}
}
void updatePos(short row,short col)
{
	space[row][col]=5;
}
void resetPos(short row,short col)
{
	space[row][col]=1;
}
bool isGoal(int i,int j)
{
	if(space[i][j]==6)
	return true;
	else return false;
}
void moveForward(Node *node)
{
	if(isInSpace()==true)
	{
//		if(space[SI][SJ]!=9)
//		{
		int pi,pj;
			checkDir(SI,SJ);
			
			if(lefT==true)
			{
				cout<<"Left is Open\n";
			}
			if(righT==true)
			{
				cout<<"Right is Open\n";
			}
			if(front==true)
			{
				
				if(dir=='L')
				{
					if(space[SI][SJ-1]!=9){
					pi = SI;pj=SJ-1;
					if(isGoal(pi,pj)==true && node!=NULL)
					{
						cout<<"whats'up\n";
						int ab;cin>>ab;
						node->isDiscovered = true;
					}
					updatePos(SI,SJ-1);
					resetPos(SI,SJ);
					printSpace();
					Sleep(300);
					SJ -=1;
				}else goal = true;
				}
				else if(dir =='R')
				{
					if(space[SI][SJ+1]!=9){
					pi = SI;pj=SJ+1;
					if(isGoal(pi,pj)==true && node!=NULL)
					{
						cout<<"whats'up\n";
						int ab;cin>>ab;
						node->isDiscovered = true;
					}
					updatePos(SI,SJ+1);
					resetPos(SI,SJ);
					printSpace();
					Sleep(300);
					SJ +=1;
				}else goal = true;
				}
				else if(dir =='U')
				{
					if(space[SI-1][SJ]!=9){
					pi = SI-1;pj=SJ;
					if(isGoal(pi,pj)==true && node!=NULL)
					{
						cout<<"whats'up\n";
						int ab;cin>>ab;
						node->isDiscovered = true;
					}
					updatePos(SI-1,SJ);
					resetPos(SI,SJ);
					printSpace();
					Sleep(300);
					SI -=1;
				}else goal = true;
				}
				else if(dir =='D')
				{
					if(space[SI+1][SJ]!=9){
					pi = SI+1;pj=SJ;
					if(isGoal(pi,pj)==true && node!=NULL)
					{
						cout<<"whats'up\n";
						int ab;cin>>ab;
						node->isDiscovered = true;
					}
					updatePos(SI+1,SJ);
					resetPos(SI,SJ);
					printSpace();
					Sleep(300);
					SI +=1;
				}else goal = true;
				}
				setGoalPos(pi,pj);
			}
			else front = false;	
			
//		}
//		else{
//			goal = true;
//		}
	}
	else cout<<" Not In Space\n";

}
void updateID()
{
	ID++;
}
int assignID()
{
	return ID;
}
int nid=1;
int returnNID()
{
	return nid++;
}
void initializeNode(Node *node,char dirFromPar,char dirInMaz,bool isDis,Node *lefChi,Node *midChi,Node *righChi,Node *parPo,int ID,int nid)
{
	node->dirFromParent=dirFromPar;
	node->dirInMaze=dirInMaz;
	node->isDiscovered =isDis;
	node->leftChild = lefChi;
	node->middleChild=midChi;
	node->rightChild = righChi;
	node->parentPointer=parPo;
	node->ID = ID;
	node->NID=nid;
}
void initializeRoot()
{
	initializeNode(root,'A','A',false,NULL,NULL,NULL,NULL,assignID(),0);
	updateID();
	Q.push(root);
	root->isRoot=true;
	cout<<"root as pointer :"<<sizeof(root)<<endl;
	Node n;
	cout<<"root using * op :"<<sizeof(*root)<<endl;int x ;cin>>x;
}

void exploreChilds(Node *node)
{
	if(node->isDiscovered==false)
	{
		checkDir(SI,SJ);
		while(front==true && righT==false && lefT==false)
		{
			moveForward(node);
			checkDir(SI,SJ);
		}
		if(lefT==true)
		{
			Node *tem = new Node();
			initializeNode(tem,'l','l',false,NULL,NULL,NULL,node,assignID(),returnNID());
			node->leftChild=tem;
			Q.push(tem);
			// the below is forward child or right
			if(front==true)
			{
				Node *tem = new Node();	
				initializeNode(tem,'m','f',false,NULL,NULL,NULL,node,assignID(),returnNID());
				node->middleChild=tem;
				Q.push(tem);
				//cout<<"two childs\n";
			}
			 if(righT==true)
			{
				Node *tem = new Node();	
				initializeNode(tem,'r','r',false,NULL,NULL,NULL,node,assignID(),returnNID());
				node->rightChild=tem;
				Q.push(tem);
				//cout<<"two childs\n";
			}
			updateID();
		}
		 else if(righT==true)
		{
			if(lefT==true)
			{
				Node *tem = new Node();
				initializeNode(tem,'l','l',false,NULL,NULL,NULL,node,assignID(),returnNID());
				node->leftChild=tem;
				Q.push(tem);
				//cout<<"two childs\n";
			}
			if(front==true)
			{
				Node *tem = new Node();
				initializeNode(tem,'m','f',false,NULL,NULL,NULL,node,assignID(),returnNID());
				node->middleChild=tem;
				Q.push(tem);
				//cout<<"two childs\n";
			}// left child as front of left in maze
			Node *tem = new Node();
			initializeNode(tem,'r','r',false,NULL,NULL,NULL,node,assignID(),returnNID());
			node->rightChild=tem;
			Q.push(tem);
			
		
			updateID();
		}
		//int ds; cin>>ds;
	}
	
}
void printNodeDe(Node *node)
{
	cout<<"DirPar :"<<node->dirFromParent<<endl;
	cout<<"DirMaz :"<<node->dirInMaze<<endl;
	cout<<"dis :"<<node->isDiscovered<<endl;
	cout<<"leftChi :"<<node->leftChild <<endl;
	cout<<"rightChi :"<<node->rightChild <<endl;
	cout<<"parent :"<<node->parentPointer<<endl;
	cout<<"ID :"<<node->ID<<endl;
}
void firstRun()
{
	Node *first = Q.top();
	Q.pop();
	exploreChilds(first);
	preNode = first;
//	root->leftChild = Q.top();
//	root->rightChild = Q.back();
}
void mapDirToParent(char dir)
{
	if(dir =='l')
	{
		changeDirToRight();
		moveForward(NULL);
		changeDirDE();
	}
	else if(dir=='r')
	{
		changeDirToLeft();
		moveForward(NULL);
		changeDirDE();
	}
	else if(dir=='f')
	{
		moveForward(NULL);
		changeDirDE();
	}
}
void backToParent(Node *node)
{
	changeDirDE();
	moveForward(NULL);
	checkDir(SI,SJ);
	while(front==true && lefT==false && righT==false)
	{
		moveForward(NULL);
		checkDir(SI,SJ);
	}
	mapDirToParent(node->dirInMaze);
}
void displayQ(queue<int> tem)
{
	cout<<"displaying queue\n";
	while(tem.size()!=0){
		cout<<tem.front()<<" | ";
		tem.pop();
	}
	cout<<endl;
}
int pos =-1;
int returnCommonNID(queue<int> pre,queue<int> tar)
{
	int tem1,tem2,val;
	queue<int> hold;
	bool found = false;
	while(pre.size()!=0)
	{
		tem1=pre.front();
		while(tar.size()!=0)
		{
			tem2 = tar.front();
			if(tem1==tem2)
			{
				val = tem1;
				found = true;
				break;
			}
			hold.push(tem2);
			tar.pop();
		}
		if(found == true)
		{
			break;
		}
		while(hold.size()!=0)
		{
			tar.push(hold.front());
			hold.pop();
		}
		pre.pop();
	}
	return val;
}
int posOfCommon(int x,queue<int> tem)
{
	int count = -1;
	if(tem.size()==1)
	{
		return 0;	
	}
	else
	{
		count=0;
		while(tem.empty()==false)
		{
			if(tem.front()==x)
			break;
			count++;
			tem.pop();
		}
		return count;
	}
}
char preDir,tarDir;
int index;
string returnCommonParent()
{
	queue<int> pre;
	queue<int> tar;
	Node *tt1,*tt2;
	tt1=preNode;
	tt2=targetNode;
	while(tt1!=NULL )	
	{
		ostringstream c1,c2,c3,c4;
			pre.push(tt1->NID);
			c3 <<tt1->dirInMaze;
			preNodeToCPDir.append(c3.str());
			tt1 = tt1->parentPointer;
	}
	while( tt2!=NULL  ){
		ostringstream c1,c2,c3,c4;
			tar.push(tt2->NID);
			c4 <<tt2->dirInMaze;
			CPToTargetDir.append(c4.str());
			tt2 = tt2->parentPointer;
		
		//cout<<"entered !!!"<<endl;
	}

	displayQ(pre);
	displayQ(tar);
	int theVar = returnCommonNID(pre,tar);

	preNodeToCPDir = preNodeToCPDir.substr(0,posOfCommon(theVar,pre));
	CPToTargetDir = CPToTargetDir.substr(0,posOfCommon(theVar,tar));
	preDir = preNodeToCPDir[preNodeToCPDir.length()-1];
	tarDir = CPToTargetDir[CPToTargetDir.length()-1];
//	cout<<"preN :"<<preNodeToCPDir<<endl;
//	cout<<"tarN :"<<CPToTargetDir<<endl;
	return "";
}
void maping(char tem,char t)
{
	char x = t;
	if(x=='l')
	{
		if(tem=='r')
		{
			moveForward(NULL);
		}else
		{
			changeDirToLeft();
			moveForward(NULL);
		}
	}
	else if(x=='r')
	{
		if(tem=='l')
		{
			moveForward(NULL);
		}
		else
		{
			changeDirToRight();
			moveForward(NULL);
		}
	}
	else
	{
		if(tem=='l')
		{
			changeDirToRight();
			moveForward(NULL);
		}
		else
		{
			changeDirToLeft();
			moveForward(NULL);
		}
	}
}

string reverseDir(string st)
{
	string hold="";
	for(int i=0;i<st.length();i++)
	{
		if(st[i]=='l')
		{
			hold +='r';
		}
		else if(st[i]=='r')
		{
			hold +='l';
		}
		else
		{
			hold +='f';
		}
	}
	return hold;
}
void moveToCommonParent(string stt,char x,char y)
{
bool sh=false;
	string tem="";
	string ho =stt;
	if(stt.length()!=0)
	{
		if(x!=y &&preNode->isRoot==false)	
	{
		tem = reverseDir(stt);
		stt = tem;
		changeDirDE();
		sh = true;
	}
	if(stt.length()!=0)
	{
		for(int k=0;k<stt.length()-1&&stt.length()>0;k++)
		{
			
			if(stt[k]=='l')
					{
						checkDir(SI,SJ);
						while(lefT==false)
						{
							moveForward(NULL);
							checkDir(SI,SJ);
						}
						changeDirToLeft();
						moveForward(NULL);
					}
					else if(stt[k]=='r')
					{
						checkDir(SI,SJ);
						while(righT==false)
						{
							moveForward(NULL);
							checkDir(SI,SJ);
						}
						changeDirToRight();
						moveForward(NULL);
					}
					else
					{
						checkDir(SI,SJ);
						while(righT==false && lefT==false && front==true)
						{
							moveForward(NULL);
							checkDir(SI,SJ);
						}
						moveForward(NULL);
					}
		}
		if(stt[stt.length()-1]=='f')
		{
			checkDir(SI,SJ);
			while(righT==false && lefT==false && front==true)
				{
					moveForward(NULL);
					checkDir(SI,SJ);
				}	
					maping(CPToTargetDir[CPToTargetDir.length()-1],ho[ho.length()-1]);
					
		}
		else 
		{
			if(stt[stt.length()-1]=='l')
					{
						checkDir(SI,SJ);
						while(lefT==false)
						{
							moveForward(NULL);
							checkDir(SI,SJ);
						}
						
						
					maping(CPToTargetDir[CPToTargetDir.length()-1],ho[ho.length()-1]);
				
					}
					else if(stt[stt.length()-1]=='r')
					{
						checkDir(SI,SJ);
						while(righT==false)
						{
							moveForward(NULL);
							checkDir(SI,SJ);
						}
					maping(CPToTargetDir[CPToTargetDir.length()-1],ho[ho.length()-1]);
						
					}
				
		
					
		}	
	}
	else cout<<"in parent\n";
	}
	
}

void moveToTarget(string st)
{
	int i=-1;
	if(st.length()>1)
		i=st.length()-2;
	else if(preNode->isRoot==true ||(preNodeToCPDir.length()==0 && CPToTargetDir.length()==1))
		i=st.length()-1;
	
	for(;i>=0;i--)
	{
		if(st[i]=='l')
				{
					checkDir(SI,SJ);
					while(lefT==false)
					{
						moveForward(NULL);
						checkDir(SI,SJ);
					}
					changeDirToLeft();
					moveForward(NULL);
				}
				else if(st[i]=='r')
				{
					checkDir(SI,SJ);
					while(righT==false)
					{
						moveForward(NULL);
						checkDir(SI,SJ);
					}
					changeDirToRight();
					moveForward(NULL);
				}
				else
				{
					checkDir(SI,SJ);
					while(righT==false && lefT==false && front==true)
					{
						moveForward(NULL);
						checkDir(SI,SJ);
					}
					moveForward(NULL);
				}	
	}
}
void moveIndirectly(Node *node)
{
	returnCommonParent();
	cout<<"pass return com\n";
	moveToCommonParent(preNodeToCPDir,preDir,tarDir);
	cout<<"pass move to comm\n";
	cout<<"leng :"<<CPToTargetDir.length()<<endl;
	moveToTarget(CPToTargetDir);
	cout<<"pass move to tar\n";
	int x;cin>>x;
	exploreChilds(node);
	changeDirDE();
	moveForward(NULL);
	changeDirDE();
	preNodeToCPDir="";
	preNodeToCPID="";
	CPToTargetDir="";
	targetNodeToCPID="";
}
string shortPath(Node *node)
{
	string tem="";
	while(node!=NULL)
	{
		tem +=node->dirInMaze;
		node = node->parentPointer;
	}
	return tem;
}
int co()
{
	Node *t = root;
	queue<Node*> fq ;
	fq.push(t);
	int cc = 0;
	while(fq.empty()==false)
	{
		cc++;
		Node *n = fq.front();
		if(n->isDiscovered==true){
		cout<<"the goal details :"<<"ID="<<n->ID<<" | "<<"dir. in maze="<<n->dirInMaze<<endl;
		cout<<"shortest path :"<<shortPath(n)<<endl;
		}
		if(n->leftChild!=NULL)
		{
			fq.push(n->leftChild);
			cout<<n->leftChild<<endl;
		}
		if(n->rightChild!=NULL)
		{
			fq.push(n->rightChild);
			cout<<n->rightChild<<endl;
		}
		if(n->middleChild!=NULL)
		{
			fq.push(n->middleChild);
			cout<<n->middleChild<<endl;
		}
		fq.pop();
	}
	
	return cc;
}
main()
{
	short val = 4;
	Node *p;
	initializeRoot();
	
	do
	{
		
		cout<<"1) Fill Space\n2) Print Space\n3) Set Goal\n4) Search\n:";cin>>val;
		if(val==1)
		{
			short sI,eI,sJ,eJ;
			cin>>sI;cin>>eI;cin>>sJ;cin>>eJ;
			fillSpace(sI-1,eI-1,sJ-1,eJ-1);
		}
		else if(val==2) printSpace();
		else if(val==3) 
		{
//			cin>>sI;cin>>sJ;
//			setGoalPos(sI-1,sJ-1);
		}
		else if(val ==4)
		{
			firstRun();
			while(Q.empty()==false)
			{
				Node *node = Q.top();
				Q.pop();
				targetNode = node;
				moveIndirectly(node);
				
				preID = node->ID;
				preNode = node;
			}
			
			cout<<"nodes :"<<co()<<endl;
			
		}
		else if(val == 5 ){
			goal = false;
			front = false;lefT = false;righT = false;
			SI = 0 ; SJ = 4;
		}
	}
	while(val!=0);
}
