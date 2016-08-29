// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 SENDERAPI_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// SENDERAPI_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef SENDERAPI_EXPORTS
#define SENDERAPI_API __declspec(dllexport)
#else
#define SENDERAPI_API __declspec(dllimport)
#endif

// 此类是从 SenderAPI.dll 导出的
class SENDERAPI_API CSenderAPI {
public:
	CSenderAPI(void);
	// TODO: 在此添加您的方法。
};

extern SENDERAPI_API int nSenderAPI;

SENDERAPI_API int fnSenderAPI(void);
SENDERAPI_API bool SendImg(cv::Mat imgin,const char name[],void *param = NULL);
SENDERAPI_API void SetCallBack(void *p);
