#ifndef Exception.H
#define Exception.H
#include <string>
using namespace std ;

class RuntimeException
{
    private:
		string errorMsg;
	public:
		RuntimeException(const string& err)
		{
			errorMsg = err;
		}
		string getMessage() const
		{
			return errorMsg;
		}
};
class vaildName : public RuntimeException
{
public :
    vaildName(const string &err) : RuntimeException(err) {}
};

class vaildNumber : public RuntimeException
{
public :
    vaildNumber(const string &err) : RuntimeException(err) {}
};

class NameExist : public RuntimeException
{
public :
    NameExist(const string &err) : RuntimeException(err) {}
};


#endif // Exception
