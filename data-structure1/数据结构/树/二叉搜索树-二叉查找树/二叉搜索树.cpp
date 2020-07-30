#include "二叉搜索树.h"
#include <assert.h>
//欲知树请百度二叉搜索树

//二叉搜索树插入新节点
bool InsertBtree(Btree** root, Bnode* node) {
	Bnode* tmp = NULL; 
	Bnode* parent = NULL; 

	if (!node) {
		return false; 
	}else {//清空新节点的左右子树 
		node->lchild = NULL; 
		node->rchild = NULL;
	}

	if(*root){//存在根节点 
		tmp= *root;
	}else{ //不存在根节点
		*root = node; 
		return true; 
	}

	while (tmp != NULL) {
		parent = tmp;//保存父节点 
	    //printf("父节点： %d\n", parent->data); 
		if(isLess(node->data,tmp->data)){ //新数据<tmp
			tmp = tmp->lchild;//左 //往下走
		}else{ 
			tmp = tmp->rchild;//右
		} 
	}//tmp==NULL,parent==最后一个支节点
	
	if(isLess(node->data, parent->data)){//找到空位置了，进行插入
		parent->lchild = node;
	}else{ 
		parent->rchild = node;
	}
	return true; 
}

/************************ * 采用二叉搜索树上最大的结点 *************************/ 
int findMax(Btree* root) { 
	assert(root != NULL);//断言;成立,程序正常;不成立,报错&终止程序

	/*
	//方式一:采用递归
	if(root->rchild==NULL){ 
		return root->data;
	}
	return findMax(root->rchild);*/

	//方式二:采用循环
	while (root->rchild) {
		root = root->rchild;
	}
	return root->data;
}

/************************ * 采用递归方式查找结点 *************************/ 
Btree* DeleteNode(Btree* root, int key, Bnode* &deletedNode) { 
	if(root==NULL)return NULL;//没有找到删除结点

	if(root->data > key) {
		root->lchild = DeleteNode(root->lchild, key, deletedNode);
		return root;
	}

	if(root->data < key) 
	{ 
		root->rchild = DeleteNode(root->rchild, key, deletedNode);
		return root;
	}

	deletedNode = root; 
	
	//删除节点不存在左右子节点，即为叶子节点，直接删除 
	if(root->lchild==NULL && root->rchild==NULL)return NULL; 

	//删除节点存在右子节点，直接用右子节点取代删除节点 
	if(root->lchild==NULL && root->rchild!=NULL)return root->rchild;
	
	//删除节点存在左子节点，直接用左子节点取代删除节点 
	if(root->lchild!=NULL && root->rchild==NULL)return root->lchild; 

	//删除节点存在左右子节点，直接用左子节点最大值取代删除节点 
	int val = findMax(root->lchild); root->data=val;
	root->lchild = DeleteNode(root->lchild,val, deletedNode);
	return root; 
}

/************************ * 采用递归方式查找结点 *************************/
Bnode* QueryByRec(Btree *root, ElemType e){ 
	if (isEqual(root->data, e) || NULL == root){ 
		return root; 
	} else if(isLess(e, root->data)) { 
		return QueryByRec(root->lchild, e);
	} else { 
		return QueryByRec(root->rchild, e); 
	} 
}

/** * 使用非递归方式查找结点 */
Bnode* QueryByLoop(Bnode *root, int e){ 
	while(NULL != root && !isEqual(root->data, e)){ 
		if(isLess(e, root->data)){ 
			root = root->lchild;
		}else{ 
			root = root->rchild; 
		} 
	}return root; 
}

/************************ * 采用递归方式实现前序遍历 *************************/ 
void PreOrderRec(Btree* root) { 
	if (root == NULL) { 
		return; 
	}
	printf("- %d -", root->data);
	PreOrderRec(root->lchild); 
	PreOrderRec(root->rchild); 
}

/************************ * 借助栈实现前序遍历 *************************/
void PreOrder(Btree* root) {
	Bnode cur; 
	if (root == NULL) { 
		return; 
	}
	SqStack stack; 
	InitStack(stack); 
	PushStack(stack, *root); //头节点先入栈

	while (!(IsEmpty(stack))) //栈为空，所有节点均已处理 
	{ 
		PopStack(stack, cur); //要遍历的节点 //出栈
		printf("- %d -", cur.data); 
		if (cur.rchild != NULL) {
			PushStack(stack, *(cur.rchild)); //右子节点先入栈，后处理
		}
		if (cur.lchild != NULL) { 
			PushStack(stack, *(cur.lchild)); //左子节点后入栈，接下来先处 理 
		}
	}

	DestroyStack(stack); 
}

int main(void) {
	int test[] = { 19, 7, 25, 5, 11, 15, 21, 61 }; 
	Bnode* root = NULL, * node = NULL; 
	node = new Bnode; 
	node->data = test[0]; 
	InsertBtree(&root, node);//插入根节点
	for(int i=1;i<sizeof(test)/sizeof(test[0]);i++){
		node = new Bnode; 
		node->data = test[i]; 
		if(InsertBtree(&root, node)){
			printf("节点 %d 插入成功\n", node->data);
		}else {
		
		}
	}
	printf("前序遍历结果： \n"); 
	PreOrderRec(root); 
	printf("\n"); 
	system("pause"); 
	//二叉搜索树删除 
	printf("删除节点 15\n"); 
	Bnode *deletedNode = NULL; 
	root = DeleteNode(root, 15, deletedNode); 
	printf("二叉搜索树删除节点 15, %s\n", deletedNode?"删除成功":"删除不 成功，节点不存在");
	if(deletedNode) delete deletedNode;
	printf("删除后，再次前序遍历结果： \n");
	PreOrderRec(root); 
	printf("\n");

	//二叉搜索树查找节点 
	Bnode * node1 = QueryByLoop(root, 20);
	printf("搜索二叉搜索树，节点 20 %s\n", node1?"存在":"不存在");
	Bnode * node2 = QueryByLoop(root, 21);
	printf("搜索二叉搜索树，节点 21 %s\n", node2?"存在":"不存在");
	system("pause"); 
	return 0;
}