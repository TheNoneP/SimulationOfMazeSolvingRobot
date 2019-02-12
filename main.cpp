#include <iostream>
#include <windows.h>
#include <queue>
#include <string>
#include <sstream>
#include <conio.h>
using namespace std;
int space[11][20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                   0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
				   1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
				   0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
				   0,0,0,6,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
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
int ID=0,preID=1,nexID=1;

struct Node{
	Node *parentPointer=NULL;
	Node *leftChild=NULL;
	Node *middleChild=NULL;
	Node *rightChild=NULL;
	char dirFromParent;
	char dirInMaze;
	int ID;
	int NID;
	bool isDiscovered;
};
Node *root = new Node();
Node *preNode,*targetNode;
string preNodeToCPDir="",CPToTargetDir="";
string preNodeToCPID="",targetNodeToCPID="";
queue<Node*> Q;
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
					Sleep(20);
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
					Sleep(20);
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
					Sleep(20);
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
					Sleep(20);
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
	initializeNode(root,'f','f',false,NULL,NULL,NULL,NULL,assignID(),0);
	updateID();
	Q.push(root);
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
	Node *first = Q.front();
	Q.pop();
	exploreChilds(first);
//	root->leftChild = Q.front();
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
string returnSub(string st,int s)
{
	string tem="";
	if(s==0)return st.substr(0,st.find('|'));
	else
	{
		while(st[s]!='|')
		{
			tem +=st[s];
			s++;
		}
		return tem;
	}
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
string findDirToTar(Node *node,int com)
{
	string st="";
	while(node->NID!=com)
	{
		st +=node->dirInMaze;
		node = node->parentPointer;
	}
	return st;
}
int returnCommonParent()
{
	queue<int> pre;
	queue<int> tar;
	Node *tt1,*tt2;
	tt1=preNode;
	tt2=targetNode;
//	printNodeDe(tt1);
//	cout<<"-------------------------\n";
//	printNodeDe(tt2);
//cout<<"tt1 :"<<tt1<<en dl;
//cout<<"tt2 :"<<tt2<<endl;
//cout<<"root :"<<root<<endl;
//cout<<tt1->ID<<endl;

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
	cout<<"pre size"<<pre.size()<<endl;
	cout<<"tar size"<<tar.size()<<endl;
	cout<<"dir :"<<preNodeToCPDir<<endl;
	cout<<"dir2 :"<<CPToTargetDir<<endl;
	displayQ(pre);
	displayQ(tar);
	int theVar = returnCommonNID(pre,tar);
	cout<<"common is :"<<theVar<<endl;
	tt2 = targetNode;
	CPToTargetDir = findDirToTar(tt2,theVar);
	bool found = false;
	string c;
	int ind = -1,coc=0;
	cin>>ind;
//	for(int i=0;i<preNodeToCPID.length();i++){
//		for(int j=0;j<targetNodeToCPID.length();j++)
//			if(preNodeToCPID[i]==targetNodeToCPID[j]){
//			c = preNodeToCPID[i];
//			ind = i;
//			coc++;
//		}
//		if(coc>1)break;
//	}
//	preNodeToCPID = preNodeToCPID.substr(0,preNodeToCPID.find(c));
//	preNodeToCPDir = preNodeToCPDir.substr(0,preNodeToCPID.length());
//	targetNodeToCPID = targetNodeToCPID.substr(0,targetNodeToCPID.find(c));
//	CPToTargetDir = CPToTargetDir.substr(0,targetNodeToCPID.length());
//	cout<<"id :"<<preNodeToCPID<<endl;
//	cout<<"id :"<<targetNodeToCPID<<endl;
//	cout<<"dir :"<<preNodeToCPDir<<endl;
//	cout<<"dir2 :"<<CPToTargetDir<<endl;
//	cout<<"common parent ID :"<<c<<endl;
//	int xd ;cin>>xd;
	return theVar;
}
void moveDirectly(Node *node)
{
	char DIM = node->dirInMaze;
	if(DIM=='l')
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
	else if(DIM=='r')
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
		moveForward(NULL);
		moveForward(NULL);
	}
	exploreChilds(node);
	cout<<"going to backToParent()\n";
	backToParent(node);
}
void moveToCommonParent()
{
	int id = returnCommonParent();
	//cout<<"idD :"<<id<<endl;
	if(preNodeToCPDir.length()>0)
	{
//		cout<<"length :"<<preNodeToCPDir.length()<<endl;
//		cout<<"preIDs :"<<preNode->ID<<endl;
//		cout<<"preNode :"<<preNode<<endl;
		while(preNode->NID!=id && preNode!=NULL)
		{
//			cout<<"backing \n";
			backToParent(preNode);
			preNode = preNode->parentPointer;
		}
	}
//	else cout<<"already in parent !\n";
	
}
void moveToTarget(Node *node)
{
	//int xa;cin>>xa;
	for(int i=CPToTargetDir.length()-1;i>=0;i--)
	{
	//	cout<<"char by char :"<<CPToTargetDir[i]<<endl;
		
		if(CPToTargetDir[i]=='l')
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
		else if(CPToTargetDir[i]=='r')
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
		else if(CPToTargetDir[i]=='f')
		{
			checkDir(SI,SJ);
			while(front==true && (lefT==false && righT==false))
			{
				moveForward(NULL);
				checkDir(SI,SJ);
			}
			moveForward(NULL);
//			moveForward();
//			checkDir(SI,SJ);
//			while(front==true && lefT==false && righT ==false)
//			{
//				moveForward();
//				checkDir(SI,SJ);
//			}
		}
	}
}
void moveIndirectly(Node *node)
{
	moveToCommonParent();
	moveToTarget(NULL);
	exploreChilds(node);
	backToParent(node);
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
	short sI,eI,sJ,eJ;
	initializeRoot();
	int x;
	cout<<sizeof(int*);
	cin>>x;
	BArray[itr]=Con;
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
			cin>>sI;cin>>sJ;
			setGoalPos(sI-1,sJ-1);
		}
		else if(val ==4)
		{
			firstRun();
			
			while(Q.empty()==false)
			{
				Node *node = Q.front();
				//printNodeDe(node);
				cout<<"\npreID :"<<preID<<"\nnode ID :"<<node->ID<<endl;
				//int xy;cin>>xy;
				if(preID==node->ID)
				{
					moveDirectly(node);
				}
				else 
				{
					targetNode = node;
					moveIndirectly(node);
				}
//				cout<<"\n New Node\n";
//				cout<<"Q size :"<<Q.size()<<endl;
				preID= node->ID;
				preNode = node->parentPointer;
				Q.pop();
				//int xx;cin>>xx;
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
