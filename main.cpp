#include <iostream>
#include <windows.h>
#include <queue>
#include <string>
#include <sstream>
#include <conio.h>
using namespace std;
int space[10][20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                   0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
				   1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
				   0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
				   0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
				   0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
				   0,0,0,1,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,
				   0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
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
	Node *rightChild=NULL;
	char dirFromParent;
	char dirInMaze;
	int ID;
	bool isDiscovered;
};
Node *root = new Node();
Node *preNode,*targetNode;
string preNodeToCPDir="",CPToTargetDir="";
string preNodeToCPID="",targetNodeToCPID="";
queue<Node> Q;
void fillSpace(short sI,short eI,short sJ,short eJ)
{
	for(int i=sI;i<=eI;i++)
		for(int j=sJ;j<=eJ;j++)
			space[i][j]=1;
}
void setGoalPos(short row,short col)
{
	space[row][col]=9;
}
void printSpace()
{
	for(int i=0;i<10;i++){
		for(int j=0;j<20;j++){
			cout<<space[i][j]<<" | ";
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<endl;
	cout<<endl;
}
bool isInSpace()
{
	if((SI<=9 && SI>=0) && (SJ>=0 && SJ<=19))
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
		else if(SI<0)SI=0;
		if(SJ>19)SJ=19;
		else if(SJ<0)SJ=0;
		
	}
	if(dir =='L')
	{
		// check front
		if(J>0){
		if(space[I][J-1]!=0) front = true;
		else front = false;
	}else front = false;
		// check left 
		if(I<9){
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
		if(I<9){
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
		if(I<9){
		if(space[I+1][J]==1) front = true;
		else front= false;
	}else front = false;
		// check left 
		if(J<19){
		if(space[I][J+1]==1) lefT = true;
		else lefT = false;
	}else lefT = false;
		// check right
		if(J>0){
		if(space[I][J-1]==1) righT = true;
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
void moveForward()
{
	if(isInSpace()==true)
	{
		if(space[SI][SJ]!=9)
		{
		
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
					updatePos(SI+1,SJ);
					resetPos(SI,SJ);
					printSpace();
					Sleep(300);
					SI +=1;
				}else goal = true;
				}
			}
			else front = false;	
		} else goal = true;
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
void initializeNode(Node *node,char dirFromPar,char dirInMaz,bool isDis,Node *lefChi,Node *righChi,Node *parPo,int ID)
{
	node->dirFromParent=dirFromPar;
	node->dirInMaze=dirInMaz;
	node->isDiscovered =isDis;
	node->leftChild = lefChi;
	node->rightChild = righChi;
	node->parentPointer=parPo;
	node->ID = ID;
}
void initializeRoot()
{
	initializeNode(root,'f','f',false,NULL,NULL,NULL,assignID());
	updateID();
	Q.push(*root);
}

void exploreChilds(Node *node)
{
	if(node->isDiscovered==false)
	{
		checkDir(SI,SJ);
		while(front==true && righT==false && lefT==false)
		{
			moveForward();
			checkDir(SI,SJ);
		}
		if(lefT==true)
		{
			Node *tem = new Node();
			initializeNode(tem,'l','l',false,NULL,NULL,node,assignID());
			node->leftChild=tem;
			Q.push(*tem);
			// the below is forward child or right
			if(front==true)
			{
				Node *tem = new Node();	
				initializeNode(tem,'r','f',false,NULL,NULL,node,assignID());
				node->rightChild=tem;
				Q.push(*tem);
			}
			else if(righT==true)
			{
				Node *tem = new Node();	
				initializeNode(tem,'r','r',false,NULL,NULL,node,assignID());
				node->rightChild=tem;
				Q.push(*tem);
			}
			updateID();
		}
		else if(righT==true)
		{
			if(lefT==true)
			{
				Node *tem = new Node();
				initializeNode(tem,'l','l',false,NULL,NULL,node,assignID());
				node->leftChild=tem;
				Q.push(*tem);
			}
			else if(front==true)
			{
				Node *tem = new Node();
				initializeNode(tem,'l','f',false,NULL,NULL,node,assignID());
				node->leftChild=tem;
				Q.push(*tem);
			}// left child as front of left in maze
			Node *tem = new Node();
			initializeNode(tem,'r','r',false,NULL,NULL,node,assignID());
			node->rightChild=tem;
			Q.push(*tem);
			
		
			updateID();
		}
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
	Node *first = &Q.front();
	Q.pop();
	exploreChilds(first);
	
}
void mapDirToParent(char dir)
{
	if(dir =='l')
	{
		changeDirToRight();
		moveForward();
		changeDirDE();
	}
	else if(dir=='r')
	{
		changeDirToLeft();
		moveForward();
		changeDirDE();
	}
	else if(dir=='f')
	{
		moveForward();
		changeDirDE();
	}
}
void backToParent(Node *node)
{
	changeDirDE();
	moveForward();
	checkDir(SI,SJ);
	while(front==true && lefT==false && righT==false)
	{
		moveForward();
		checkDir(SI,SJ);
	}
	mapDirToParent(node->dirInMaze);
}
char returnCommonParent()
{
	
	Node *tt1,*tt2;
	tt1=preNode;
	tt2=targetNode;
//	printNodeDe(tt1);
//	cout<<"-------------------------\n";
//	printNodeDe(tt2);
cout<<"tt1 :"<<tt1<<endl;
cout<<"tt2 :"<<tt2<<endl;
cout<<"root :"<<root<<endl;
cout<<tt1->ID<<endl;
int fd;cin>>fd;
	while(tt1!=NULL && tt1->ID <= assignID() )	
	{
		ostringstream c1,c2,c3,c4;
			c2 <<tt1->ID;
			cout<<"id par :"<<tt1->ID<<endl;
			
			preNodeToCPID.append(c2.str());
			c3 <<tt1->dirInMaze;
			preNodeToCPDir.append(c3.str());
			tt1 = tt1->parentPointer;
	}
	while( tt2!=NULL && tt2->ID <= assignID()){
		ostringstream c1,c2,c3,c4;
		if(tt2!=NULL){
			c1 << tt2->ID;
			targetNodeToCPID.append(c1.str());
			c4 <<tt2->dirInMaze;
			CPToTargetDir.append(c4.str());
			tt2 = tt2->parentPointer;
		}
		cout<<"entered !!!"<<endl;
	}
	cout<<"id :"<<preNodeToCPID<<endl;
	cout<<"id :"<<targetNodeToCPID<<endl;
	cout<<"dir :"<<preNodeToCPDir<<endl;
	cout<<"dir2 :"<<CPToTargetDir<<endl;
	bool found = false;
	char c;
	int ind = -1;
	for(int i=0;i<preNodeToCPID.length();i++){
		for(int j=0;j<targetNodeToCPID.length();j++)
			if(preNodeToCPID[i]==targetNodeToCPID[j]){
			c = preNodeToCPID[i];
			ind = i;
		}
	}
	preNodeToCPID = preNodeToCPID.substr(0,preNodeToCPID.find(c));
	preNodeToCPDir = preNodeToCPDir.substr(0,preNodeToCPID.length());
	targetNodeToCPID = targetNodeToCPID.substr(0,targetNodeToCPID.find(c));
	CPToTargetDir = CPToTargetDir.substr(0,targetNodeToCPID.length());
	cout<<"common parent :"<<c<<endl;
	cout<<"id :"<<preNodeToCPID<<endl;
	cout<<"id :"<<targetNodeToCPID<<endl;
	cout<<"dir :"<<preNodeToCPDir<<endl;
	cout<<"dir2 :"<<CPToTargetDir<<endl;
	return c;
}
void moveDirectly(Node *node)
{
	char DIM = node->dirInMaze;
	if(DIM=='l')
	{
		checkDir(SI,SJ);
		while(lefT==false)
		{
			moveForward();
			checkDir(SI,SJ);
		}
		changeDirToLeft();
		moveForward();	
	}
	else if(DIM=='r')
	{
		checkDir(SI,SJ);
		while(righT==false)
		{
			moveForward();
			checkDir(SI,SJ);
		}
		changeDirToRight();
		moveForward();
	}
	else 
	{
		moveForward();
		moveForward();
	}
	exploreChilds(node);
	backToParent(node);
}
void moveToCommonParent()
{
	int id = (int)returnCommonParent()-48;
	cout<<"idD :"<<id<<endl;
	if(preNodeToCPDir.length()>0)
	{
		cout<<"length :"<<preNodeToCPDir.length()<<endl;
		cout<<"preIDs :"<<preNode->ID<<endl;
		cout<<"preNode :"<<preNode<<endl;
		while(preNode->ID!=id && preNode!=NULL)
		{
			cout<<"backing \n";
			backToParent(preNode);
			preNode = preNode->parentPointer;
		}
	}
	else cout<<"already in parent !\n";
	
}
void moveToTarget()
{
	int xa;cin>>xa;
	for(int i=CPToTargetDir.length()-1;i>=0;i--)
	{
		cout<<"char by char :"<<CPToTargetDir[i]<<endl;
		
		if(CPToTargetDir[i]=='l')
		{
			checkDir(SI,SJ);
			while(lefT==false)
			{
				moveForward();
				checkDir(SI,SJ);
			}
			changeDirToLeft();
			moveForward();
			
		}
		else if(CPToTargetDir[i]=='r')
		{
			checkDir(SI,SJ);
			while(righT==false)
			{
				moveForward();
				checkDir(SI,SJ);
			}
			changeDirToRight();
			moveForward();
		}
		else if(CPToTargetDir[i]=='f')
		{
			moveForward();
			moveForward();
			checkDir(SI,SJ);
			while(front==true && lefT==false && righT ==false)
			{
				moveForward();
				checkDir(SI,SJ);
			}
		}
	}
}
void moveIndirectly(Node *node)
{
	moveToCommonParent();
	moveToTarget();
	exploreChilds(node);
	backToParent(node);
	preNodeToCPDir="";
	preNodeToCPID="";
	CPToTargetDir="";
	targetNodeToCPID="";
}
main()
{
	short val = 4;
	short sI,eI,sJ,eJ;
	initializeRoot();
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
				Node *node = &Q.front();
				//printNodeDe(node);
				cout<<"\npreID :"<<preID<<"\nnode ID :"<<node->ID<<endl;
				int xy;cin>>xy;
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
				
			}
		}
		else if(val == 5 ){
			goal = false;
			front = false;lefT = false;righT = false;
			SI = 0 ; SJ = 4;
		}
	}
	while(val!=0);
}
