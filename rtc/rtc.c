// tary, 1:06 2011/9/12
#include "am18x_lib.h"
#include "auxlib.h"
#include "rtc.h"

static rtc_tm_t tm[1], tm_now[1];
static char* monthes[] = {
	"Jan", "Feb", "Mar", "Apr",
	"May", "Jun", "Jul", "Aug",
	"Sep", "Oct", "Nov", "Dec",
};

int rtc_operation(void) {
	unsigned year, month, day, hour, minute, second;
	char buf[0x100], month_buf[0x20];
	int i;

	sprintf(buf, "%s %s", __DATE__, __TIME__);
	sscanf(buf, "%s %d %d %d:%d:%d", month_buf, &day, &year, &hour, &minute, &second);

	for (i = 0; i < countof(monthes); i++) {
		if (strcmp(monthes[i], month_buf) == 0) {
			month = i + 1;
			break;
		}
	}
	printk("%.4d-%.2d-%.2d %.2d:%.2d:%.2d\n", year, month, day, hour, minute, second);

	tm->cflags = RTC_ENABLE;
	rtc_conf(RTC, tm);

	rtc_state(RTC, tm_now);
	if (tm_now->minute != minute) {
		tm->year = year;
		tm->month = month;
		tm->day = day;
		tm->hour = hour;
		tm->minute = minute;
		tm->second = second;
		tm->cflags = RTC_SET_TIME;
		rtc_conf(RTC, tm);
	}

	printk("the time now:\t");
	printk("%.4d-%.2d-%.2d %.2d:%.2d:%.2d weekday = %.1d\n",
		tm_now->year,
		tm_now->month,
		tm_now->day,
		tm_now->hour,
		tm_now->minute,
		tm_now->second,
		tm_now->weekday
	);

	return 0;
}
