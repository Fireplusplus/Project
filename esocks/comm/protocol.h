#pragma once


// 将对齐方式设置为1字节对齐,防止中间产生空白
#pragma pack(push)
#pragma pack(1)

// 验证数据包格式
// client sock request
struct SKReq
{
	char ver;	// 在SOCKS5中VER字节总是0，代表socks5
	char n;		// 存放客户端可以接受的认证方法数量(单位字节)
};

// server sock reply
struct SKRep
{
	char ver;	
	char m;		// 这里只用到'00',代表验证为不验证
};

// 请求数据包格式
// client request
struct AddrReq
{
	// VER | CMD |  RSV  | ATYP | DST.ADDR | DST.PORT
	char ver;	// protocol version:'05'
	char cmd;	// CONNECT: '01'
	char rsv;	// RESERVED
	char atype;	// address type of following address.ipv4:'01' DOMAINNAME:'03'
	// 地址为变长
};

struct AddrRep
{
	// VER | REP |  RSV  | ATYP | BND.ADDR | BND.PORT
	char ver;
	char cmd; 	// reply cmd: succesd:'00'
	char rsv;	
	char atype;
	int addr;	
	short port;
};

#pragma pack(pop)


