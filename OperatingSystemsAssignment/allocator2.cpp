#include"allocator2.h"


	node::node()
	{
		left = NULL;
		allocated = 0;
		right = NULL;
		parent = NULL;
	}

	 allocator2::allocator2()
	{
		 root = new node();
	}

	int allocator2::getlevel(int size)
	{
		return 10 - int(ceil(log2(size)));
	}

	bool allocator2::allocatenode(int level, int currentlevel,node * n)
	{
		if (level == currentlevel)
		{
			if (n->left == NULL && n->right == NULL&&n->allocated==false)

			{
				n->allocated = 1;
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			if (n->left == NULL)
			{
				n->left = new node();
				n->left->parent = n;
				return allocatenode(level, currentlevel + 1, n->left);
			}
			else if (n->right == NULL)
			{
				n->right = new node();
				n->right->parent = n;
				return allocatenode(level, currentlevel + 1, n->right);
			}
			else
			{
				if(n->left->allocated==true)
					return allocatenode(level, currentlevel + 1, n->right);
				else 
					return allocatenode(level, currentlevel + 1, n->left);
			}
			//if(allocatenode(level,currentlevel+1,n->left))
		}
		
			if (tempr != NULL)
			{
				
			}
	
  }



