#pragma once
#include "ebase.h"
#include <random>

namespace e2d
{

class TimerManager;
class MusicManager;

// 随机数产生器
class Random
{
public:
	// 取得整型范围内的一个随机数
	template<typename T>
	static inline T range(T min, T max) { return e2d::Random::randomInt(min, max); }

	// 取得浮点数范围内的一个随机数
	static inline double range(double min, double max) { return e2d::Random::randomReal(min, max); }

	// 取得整型范围内的一个随机数
	template<typename T>
	static T randomInt(T min, T max)
	{
		std::uniform_int_distribution<T> dist(min, max);
		return dist(getEngine());
	}

	// 取得浮点数类型范围内的一个随机数
	template<typename T>
	static T randomReal(T min, T max)
	{
		std::uniform_real_distribution<T> dist(min, max);
		return dist(getEngine());
	}

	// 获取随机数产生器
	static std::default_random_engine &getEngine();
};


// 定时器
class Timer :
	public Obj
{
	friend TimerManager;

public:
	Timer();

	Timer(
		const TimerCallback &callback,	/* 定时器回调函数 */
		double interval = 0,			/* 时间间隔（秒） */
		int repeatTimes = -1,			/* 定时器执行次数 */
		bool atOnce = false				/* 是否立即执行 */
	);

	Timer(
		const String &name,				/* 定时器名称 */
		const TimerCallback &callback,	/* 定时器回调函数 */
		double interval = 0,			/* 时间间隔（秒） */
		int repeatTimes = -1,			/* 定时器执行次数 */
		bool atOnce = false				/* 是否立即执行 */
	);

	// 启动定时器
	void start();

	// 停止定时器
	void stop();

	// 获取定时器状态
	bool isRunning() const;

	// 获取定时器名称
	String getName() const;

	// 获取定时器所在节点
	Node * getParentNode() const;

	// 设置定时器名称
	void setName(
		const String &name
	);

	// 设置定时器执行间隔（秒）
	void setInterval(
		double interval
	);

	// 设置定时器回调函数
	void setCallback(
		const TimerCallback & callback
	);

	// 设置定时器重复执行次数
	void setRepeatTimes(
		int nRepeatTimes
	);

	// 设置定时器在绑定后立即执行一次
	virtual void setRunAtOnce(
		bool bAtOnce
	);

protected:
	// 执行回调函数
	void _callOn();

	// 判断是否达到执行状态
	bool _isReady() const;

protected:
	String			m_sName;
	bool			m_bRunning;
	bool			m_bAtOnce;
	int				m_nRunTimes;
	int				m_nRepeatTimes;
	double			m_fInterval;
	double			m_fLast;
	Node *			m_pParentNode;
	TimerCallback	m_Callback;
};


// 数据管理工具
class Data
{
public:
	// 保存 int 类型的值
	static void saveInt(
		const String & key,
		int value
	);

	// 保存 double 类型的值
	static void saveDouble(
		const String & key,
		double value
	);

	// 保存 字符串 类型的值
	static void saveString(
		const String & key,
		const String & value
	);

	// 获取 int 类型的值
	// （若不存在则返回 defaultValue 参数的值）
	static int getInt(
		const String & key,
		int defaultValue
	);

	// 获取 double 类型的值
	// （若不存在则返回 defaultValue 参数的值）
	static double getDouble(
		const String & key,
		double defaultValue
	);

	// 获取 字符串 类型的值
	// （若不存在则返回 defaultValue 参数的值）
	static String getString(
		const String & key,
		const String & defaultValue
	);
};


// 文件管理工具
class File
{
public:
	// 获取系统的 AppData Local 路径
	static String getLocalAppDataPath();

	// 获取临时文件目录
	static String getTempPath();

	// 获取默认的保存路径
	static String getDefaultSavePath();

	// 获取文件扩展名
	static String getFileExtension(
		const String & filePath
	);

	// 打开保存文件对话框
	static String getSaveFilePath(
		const String & title = L"保存到",	/* 对话框标题 */
		const String & defExt = L""			/* 默认扩展名 */
	);
};


// 音乐播放器
class Music
{
	friend MusicManager;

public:
	// 播放
	bool play(
		int nLoopCount = 0	/* 重复播放次数，设置 -1 为循环播放 */
	);

	// 暂停
	bool pause();

	// 继续
	bool resume();

	// 停止
	bool stop();

	// 获取音乐播放状态
	bool isPlaying();

	// 获取音量
	double getVolume() const;

	// 设置音量
	bool setVolume(
		double fVolume	/* 音量范围为 -224 ~ 224，其中 0 是静音，1 是正常音量 */
	);

	// 获取频率比
	double getFrequencyRatio() const;

	// 设置频率比
	bool setFrequencyRatio(
		double fFrequencyRatio	/* 频率比范围为 1/1024.0f ~ 1024.0f，其中 1.0 为正常声调 */
	);

	// 获取 IXAudio2SourceVoice 对象
	IXAudio2SourceVoice* getIXAudio2SourceVoice() const;

protected:
	Music();

	virtual ~Music();

	bool _open(const String & strFileName);

	void _close();

	bool _readMMIO();

	bool _resetFile();

	bool _read(BYTE* pBuffer, DWORD dwSizeToRead);

	bool _findMediaFileCch(wchar_t* strDestPath, int cchDest, const String & strFilename);

protected:
	bool m_bOpened;
	bool m_bPlaying;
	DWORD m_dwSize;
	CHAR* m_pResourceBuffer;
	BYTE* m_pbWaveData;
	HMMIO m_hmmio;
	MMCKINFO m_ck;
	MMCKINFO m_ckRiff;
	WAVEFORMATEX* m_pwfx;
	IXAudio2SourceVoice* m_pSourceVoice;
};

}