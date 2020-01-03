#include <iostream>
#include <unistd.h>

#define NUM_BRANCH 5

using namespace std;

/* Subject Interface */
class Branch
{
public:
    virtual void ShowStock( int ) = 0;

private:
};


/* Real Subject 상속 클래스 */
class RealBranch : public Branch
{
public:
    RealBranch( int aID, int aStock )
	{
		mID = aID;	
		mStock = aStock;
	}

    void ShowStock( int /* BranchID */ ) 
	{ 
		cout << "Show Stock BranchID[" << mID << "] Stock : " << mStock << endl; 
	}


private:
    int mID;
	int mStock;
};


/* Proxy 상속 클래스 */
class ProxyBranch : public Branch
{
public:
	ProxyBranch()
	{
		int i = 0;

		for ( i = 0; i < NUM_BRANCH; i++ )
		{
			mBranches[i] = new RealBranch( i, i * 10 );
		}
	}

	~ProxyBranch() 
	{
		int i = 0;

		for ( i = 0; i < NUM_BRANCH; i++ )
		{
			if ( mBranches[i] != NULL )
			{
				delete mBranches[i];
				mBranches[i] = NULL;
			}
		}
	}

	void ShowStock( int aID )
	{
		mBranches[aID]->ShowStock( aID );
	}

private:
	RealBranch  * mBranches[NUM_BRANCH];
};

int main( void )
{
	Branch * sBranch = new ProxyBranch();
	
	sBranch->ShowStock( 1 );
	sBranch->ShowStock( 3 );

	return 0;
}