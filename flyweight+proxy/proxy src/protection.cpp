#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

/* Subject Interface */
class Data
{
public:
    virtual void getData( const char * /* aID */, const char * /* aPW */ ) = 0; 

private:
};


/* Real Subject 상속 클래스 */
class RealData : public Data
{
public:
    RealData()
	{
		strcpy( mData, "Im Data" );
	}

    void getData( const char * /* aID */, const char * /* aPW */ ) 
	{ 
		cout << "getData : " << mData << endl << endl; 
	}

private:
    char mData[20];
};


/* Proxy 상속 클래스 */
class ProxyDataMgr : public Data
{
public:
	ProxyDataMgr()
	{
		mData = new RealData();

		strcpy( mID, "design" );
		strcpy( mPW, "pattern" );
	}

	~ProxyDataMgr() 
	{
		if ( mData != NULL )
		{ 
			delete mData;
			mData = NULL;

			mID[0] = '\0';
			mPW[0] = '\0';
		}
	}

	void getData( const char * aID, const char * aPW )
	{
		if ( authCheck( aID, aPW ) == true )
		{
			cout << "ID : " << aID << endl << "PW : " << aPW << endl << " is Corret ID/PW" << endl;
			mData->getData( NULL, NULL );
		}
		else
		{
			cout << "ID : " << aID << endl << "PW : " << aPW << endl <<  " is Wrong ID/PW" << endl << endl;
		}
	}

private:
	RealData * mData;
	char 	   mID[20];
	char 	   mPW[20];

	bool authCheck( const char * aID, const char * aPW )
	{
		bool aIsCorret = false;

		if ( strcmp( aID, mID ) == 0 )
		{
			if ( strcmp( aPW, mPW ) == 0 )
			{
				aIsCorret = true;
			}
		}

		return aIsCorret;
	}
};

int main( void )
{
	Data * sData = new ProxyDataMgr();
	
	sData->getData( "wIDasdf", "wPWdf" );	
	sData->getData( "design", "pattern" );

	return 0;
}