#include <iostream>
#include <unistd.h>

using namespace std;

/* Subject Interface */
class Image
{
public:
    virtual void ShowImage() = 0;

private:
};


/* Real Subject 상속 클래스 */
class RealImage : public Image
{
public:
    RealImage( const char * aName ) : mFileName( aName ) {}

    void ShowImage() 
	{ 
		cout << "show image : " << mFileName << endl; 
	}

	void LoadImage() 
	{
		cout << "loading mFileName : " << mFileName << endl; 
		sleep( 2 );
	}

private:
    const char * mFileName;
};


/* Proxy 상속 클래스 */
class ProxyImage : public Image
{
public:
	ProxyImage( const char * aName ) : mFileName( aName )
	{
		mImage = NULL;
		mIsLoadImg = false;
	}

	~ProxyImage() 
	{
		if ( mImage != NULL )
		{ 
			delete mImage;
			mImage = NULL;

			mFileName = NULL;
			mIsLoadImg = false; 
		}
	}

	void ShowImage()
	{
		if ( mImage == NULL )
		{
			mImage = new RealImage( mFileName );
			mImage->LoadImage();
		}

		mImage->ShowImage();
	}

private:
	RealImage  * mImage;
	const char * mFileName;
	bool         mIsLoadImg;
};

int main( void )
{
	Image * sImage = new ProxyImage( "image.jpg" );
	
	sImage->ShowImage();
	sImage->ShowImage();
	sImage->ShowImage();
}