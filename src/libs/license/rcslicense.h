//dlldemo.h 
#include "nrlicense.h"

const int KEY = 1314;
const int C1 = 52845;
const int C2 = 22719;
const int C3 = 65;
const int C4 = 26;

//获取CPU的ID号
bool createCPUID(NR_INT64 & cpuID);
//获取硬盘的ID号
bool createHardID(NR_INT64 & HardID);
//获取网卡的MAC地址
//bool createMACID(NR_INT64 & macID);
//格式化字符串
bool formatLicense(char * dest, char * src);
//获取字符串中换行符前的字符串
bool getLineFromString(char * src, char * dest);

static NR_UINT julianDayFromDate(int year, int month, int day);

bool createHostIDNew1(char * sHostID, NR_INT64 macID);

bool getMacIDList(NR_INT64* pMacList, int& ncount);

NR_STATUS checkLicenseOldPrivate(const char * sSoftName);
NR_STATUS checkLicenseNewPrivate(const char * sSoftName);


#if defined(WIN32)

#include <winsock2.h>
#include <time.h>

#ifndef GAA_FLAG_INCLUDE_ALL_INTERFACES
# define GAA_FLAG_INCLUDE_ALL_INTERFACES 0x0100
#endif
#ifndef MAX_ADAPTER_ADDRESS_LENGTH
// definitions from iptypes.h
# define MAX_ADAPTER_DESCRIPTION_LENGTH  128 // arb.
# define MAX_ADAPTER_NAME_LENGTH         256 // arb.
# define MAX_ADAPTER_ADDRESS_LENGTH      8   // arb.
# define DEFAULT_MINIMUM_ENTITIES        32  // arb.
# define MAX_HOSTNAME_LEN                128 // arb.
# define MAX_DOMAIN_NAME_LEN             128 // arb.
# define MAX_SCOPE_ID_LEN                256 // arb.

# define GAA_FLAG_SKIP_UNICAST       0x0001
# define GAA_FLAG_SKIP_ANYCAST       0x0002
# define GAA_FLAG_SKIP_MULTICAST     0x0004
# define GAA_FLAG_SKIP_DNS_SERVER    0x0008
# define GAA_FLAG_INCLUDE_PREFIX     0x0010
# define GAA_FLAG_SKIP_FRIENDLY_NAME 0x0020

# define IP_ADAPTER_DDNS_ENABLED               0x01
# define IP_ADAPTER_REGISTER_ADAPTER_SUFFIX    0x02
# define IP_ADAPTER_DHCP_ENABLED               0x04
# define IP_ADAPTER_RECEIVE_ONLY               0x08
# define IP_ADAPTER_NO_MULTICAST               0x10
# define IP_ADAPTER_IPV6_OTHER_STATEFUL_CONFIG 0x20

# define MIB_IF_TYPE_OTHER               1
# define MIB_IF_TYPE_ETHERNET            6
# define MIB_IF_TYPE_TOKENRING           9
# define MIB_IF_TYPE_FDDI                15
# define MIB_IF_TYPE_PPP                 23
# define MIB_IF_TYPE_LOOPBACK            24
# define MIB_IF_TYPE_SLIP                28

#endif
// copied from qnativesocketengine_win.cpp
struct qt_in6_addr {
    u_char qt_s6_addr[16];
};
typedef struct {
    short   sin6_family;            /* AF_INET6 */
    u_short sin6_port;              /* Transport level port number */
    u_long  sin6_flowinfo;          /* IPv6 flow information */
    struct  qt_in6_addr sin6_addr;  /* IPv6 address */
    u_long  sin6_scope_id;          /* set of interfaces for a scope */
} qt_sockaddr_in6;

// copied from MSDN online help
typedef enum {
  IpPrefixOriginOther = 0, 
  IpPrefixOriginManual, 
  IpPrefixOriginWellKnown, 
  IpPrefixOriginDhcp, 
  IpPrefixOriginRouterAdvertisement
} IP_PREFIX_ORIGIN;

typedef enum {
  IpSuffixOriginOther = 0, 
  IpSuffixOriginManual, 
  IpSuffixOriginWellKnown, 
  IpSuffixOriginDhcp, 
  IpSuffixOriginLinkLayerAddress, 
  IpSuffixOriginRandom
} IP_SUFFIX_ORIGIN;

typedef enum {
    IpDadStateInvalid    = 0,
    IpDadStateTentative,
    IpDadStateDuplicate,
    IpDadStateDeprecated,
    IpDadStatePreferred,
} IP_DAD_STATE;

typedef enum {
    IfOperStatusUp = 1,
    IfOperStatusDown,
    IfOperStatusTesting,
    IfOperStatusUnknown,
    IfOperStatusDormant,
    IfOperStatusNotPresent,
    IfOperStatusLowerLayerDown
} IF_OPER_STATUS;

typedef struct _IP_ADAPTER_UNICAST_ADDRESS {
  union {
    ULONGLONG Alignment;
    struct {
      ULONG Length;
      DWORD Flags;
    };
  };
  struct _IP_ADAPTER_UNICAST_ADDRESS* Next;
  SOCKET_ADDRESS Address;
  IP_PREFIX_ORIGIN PrefixOrigin;
  IP_SUFFIX_ORIGIN SuffixOrigin;
  IP_DAD_STATE DadState;
  ULONG ValidLifetime;
  ULONG PreferredLifetime;
  ULONG LeaseLifetime;
} IP_ADAPTER_UNICAST_ADDRESS, *PIP_ADAPTER_UNICAST_ADDRESS;

typedef struct _IP_ADAPTER_ANYCAST_ADDRESS 
 IP_ADAPTER_ANYCAST_ADDRESS, *PIP_ADAPTER_ANYCAST_ADDRESS;

typedef struct _IP_ADAPTER_MULTICAST_ADDRESS 
 IP_ADAPTER_MULTICAST_ADDRESS, 
 *PIP_ADAPTER_MULTICAST_ADDRESS;

typedef struct _IP_ADAPTER_DNS_SERVER_ADDRESS
 IP_ADAPTER_DNS_SERVER_ADDRESS,
 *PIP_ADAPTER_DNS_SERVER_ADDRESS;

typedef struct _IP_ADAPTER_PREFIX {
  union {
    ULONGLONG  Alignment;
    struct {
      ULONG Length;
      DWORD Flags;
    };
  };
  struct _IP_ADAPTER_PREFIX* Next;
  SOCKET_ADDRESS Address;
  ULONG PrefixLength;
} IP_ADAPTER_PREFIX, 
 *PIP_ADAPTER_PREFIX;

typedef struct _IP_ADAPTER_ADDRESSES {
  union {
    ULONGLONG Alignment;
    struct {
      ULONG Length;
      DWORD IfIndex;
    };
  };
  struct _IP_ADAPTER_ADDRESSES* Next;
  PCHAR AdapterName;
  PIP_ADAPTER_UNICAST_ADDRESS FirstUnicastAddress;
  PIP_ADAPTER_ANYCAST_ADDRESS FirstAnycastAddress;
  PIP_ADAPTER_MULTICAST_ADDRESS FirstMulticastAddress;
  PIP_ADAPTER_DNS_SERVER_ADDRESS FirstDnsServerAddress;
  PWCHAR DnsSuffix;
  PWCHAR Description;
  PWCHAR FriendlyName;
  BYTE PhysicalAddress[MAX_ADAPTER_ADDRESS_LENGTH];
  DWORD PhysicalAddressLength;
  DWORD Flags;
  DWORD Mtu;
  DWORD IfType;
  IF_OPER_STATUS OperStatus;
  DWORD Ipv6IfIndex;
  DWORD ZoneIndices[16];
  PIP_ADAPTER_PREFIX FirstPrefix;
} IP_ADAPTER_ADDRESSES, 
 *PIP_ADAPTER_ADDRESSES;

typedef struct {
    char String[4 * 4];
} IP_ADDRESS_STRING, *PIP_ADDRESS_STRING, IP_MASK_STRING, *PIP_MASK_STRING;

typedef struct _IP_ADDR_STRING {
  struct _IP_ADDR_STRING* Next;
  IP_ADDRESS_STRING IpAddress;
  IP_MASK_STRING IpMask;
  DWORD Context;
} IP_ADDR_STRING, 
 *PIP_ADDR_STRING;

typedef struct _IP_ADAPTER_INFO {
  struct _IP_ADAPTER_INFO* Next;
  DWORD ComboIndex;
  char AdapterName[MAX_ADAPTER_NAME_LENGTH + 4];
  char Description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
  UINT AddressLength;
  BYTE Address[MAX_ADAPTER_ADDRESS_LENGTH];
  DWORD Index;
  UINT Type;
  UINT DhcpEnabled;
  PIP_ADDR_STRING CurrentIpAddress;
  IP_ADDR_STRING IpAddressList;
  IP_ADDR_STRING GatewayList;
  IP_ADDR_STRING DhcpServer;
  BOOL HaveWins;
  IP_ADDR_STRING PrimaryWinsServer;
  IP_ADDR_STRING SecondaryWinsServer;
  time_t LeaseObtained;
  time_t LeaseExpires;
} IP_ADAPTER_INFO, 
 *PIP_ADAPTER_INFO;

typedef struct {
  char HostName[MAX_HOSTNAME_LEN + 4];
  char DomainName[MAX_DOMAIN_NAME_LEN + 4];
  PIP_ADDR_STRING CurrentDnsServer;
  IP_ADDR_STRING DnsServerList;
  UINT NodeType;
  char ScopeId[MAX_SCOPE_ID_LEN + 4];
  UINT EnableRouting;
  UINT EnableProxy;
  UINT EnableDns;
} FIXED_INFO, *PFIXED_INFO;

bool interfaceListingWinXP(NR_INT64* pMacList, int& ncount);
bool interfaceListingWin2k(NR_INT64* pMacList, int& ncount);

//windows,判断是否域用户，域用户不需要注册
bool isDomainUser();

#else

using namespace std;

#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#if defined(VXWORKS)
#  include <sockLib.h>
#endif

// for inet_addr
#include <netdb.h>
#include <arpa/inet.h>
#if defined(VXWORKS)
#  include <hostLib.h>
#else
#  include <resolv.h>
#endif

#if defined(__linux__) || defined(__linux)
#  include <ifaddrs.h>
#include <errno.h>
#endif

#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
#  include <net/if_dl.h>
#endif


// UnixWare 7 redefines socket -> _socket
static inline int qt_safe_socket(int domain, int type, int protocol, int flags = 0)
{	
    register int fd;
#if defined(SOCK_CLOEXEC) && defined(SOCK_NONBLOCK)
    int newtype = type | SOCK_CLOEXEC;
    if (flags & O_NONBLOCK)
        newtype |= SOCK_NONBLOCK;
    fd = ::socket(domain, newtype, protocol);
    if (fd != -1 || errno != EINVAL)
        return fd;
#endif
	
    fd = ::socket(domain, type, protocol);
    if (fd == -1)
        return -1;
	
    ::fcntl(fd, F_SETFD, FD_CLOEXEC);
	
    // set non-block too?
    if (flags & O_NONBLOCK)
        ::fcntl(fd, F_SETFL, ::fcntl(fd, F_GETFL) | O_NONBLOCK);
	
    return fd;
}

#if defined(__aix__) || defined(__AIX__) || defined(_AIX)

	// VxWorks' headers specify 'int' instead of '...' for the 3rd ioctl() parameter.
	template <typename T>
	static inline int qt_safe_ioctl(int sockfd, int request, T arg)
	{
#	ifdef VXWORKS
		return ::ioctl(sockfd, request, (int) arg);
#	else
		return ::ioctl(sockfd, request, arg);
#	endif
	}

#endif

#endif

class LICENSE_EXPORT CRcsLicense
{
public:
	CRcsLicense();
};

