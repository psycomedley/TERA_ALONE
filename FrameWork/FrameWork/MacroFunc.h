#define MSGBOX(string) MessageBox(NULL, string, "Message", MB_OK)
#define OutputInteger(msg, string, value) \
	sprintf_s(msg, "%s : %d\n", string, value);\
	OutputDebugString(msg);\

#define OutputFloat(msg, string, value) \
	sprintf_s(msg, "%s : %f\n", string, value);\
	OutputDebugString(msg);\

#define SAFE_ADD_REF(p) if(p) { (p)->AddRef(); }
#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL; }
#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p) = NULL; }
#define SAFE_DELETE_ARRAY(p)	{ if(p) {delete[] (p); (p) = NULL;} }

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
		}\
}