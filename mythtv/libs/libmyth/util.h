#ifndef UTIL_H_
#define UTIL_H_

#include <qstringlist.h>
#include <qdatetime.h>
#include <qcolor.h>

#include <time.h>

#define MYTH_SYSTEM_DONT_BLOCK_LIRC          0x1 //< myth_system() flag to avoid blocking
#define MYTH_SYSTEM_DONT_BLOCK_JOYSTICK_MENU 0x2 //< myth_system() flag to avoid blocking

class QPixmap;
class QImage;
class QPainter;
class QFont;

class MythTimer
{
  public:
    MythTimer() {}

    void start() { m_timer.start(); }
    int restart() { int ret = elapsed(); 
                    m_timer.restart(); 
                    return ret; 
                  }
    int elapsed() { int ret = m_timer.elapsed();
                    if (ret > 86300000) { ret = 0;  m_timer.restart(); }
                    return ret;
                  }

    void addMSecs(int ms) { m_timer.addMSecs(ms); }

  private:
    QTime m_timer;
};

QDateTime mythCurrentDateTime();

// This is necessary for GCC 3.3, which has llabs(long long)
// but not abs(long long) or std::llabs(long long)
inline  long long  absLongLong(long long  n)  { return n >= 0 ? n : -n; } 

void encodeLongLong(QStringList &list, long long num);
long long decodeLongLong(QStringList &list, uint offset);
long long decodeLongLong(QStringList &list, QStringList::iterator &it);

QRgb blendColors(QRgb source, QRgb add, int alpha);

uint myth_system(const QString &command, int flags = 0);

QString cutDownString(const QString &text, QFont *testFont, uint maxwidth);

QDateTime MythUTCToLocal(const QDateTime &utc);
int MythSecsTo(const QDateTime &from, const QDateTime &to);

long long stringToLongLong(const QString &str);
QString longLongToString(long long ll);

long long getDiskSpace(const QString&,long long&,long long&);
bool getUptime(time_t &uptime);
bool getMemStats(int &totalMB, int &freeMB, int &totalVM, int &freeVM);

#endif // UTIL_H_
