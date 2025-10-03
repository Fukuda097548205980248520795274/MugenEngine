#include "Animation.h"

/// <summary>
/// 任意の時刻の値を取得する
/// </summary>
/// <param name="keyframe"></param>
/// <param name="time"></param>
/// <returns></returns>
Vector3 CalcuateValue(const std::vector<KeyFrameVector3>& keyframe, float time)
{
	// キーがないと返す値が内のでアウト
	assert(!keyframe.empty());

	// キーが一つか、時刻がキーフレーム前なら最初の値とする
	if (keyframe.size() == 1 || time <= keyframe[0].time)
	{
		return keyframe[0].value;
	}

	for (size_t index = 0; index < keyframe.size() - 1; ++index)
	{
		size_t nextIndex = index + 1;

		// index と nextIndex
		if (keyframe[index].time <= time && time <= keyframe[nextIndex].time)
		{
			// 範囲内を補完する
			float t = (time - keyframe[index].time) / (keyframe[nextIndex].time - keyframe[index].time);
			return Lerp(keyframe[index].value, keyframe[nextIndex].value, t);
		}
	}

	// ここまで来たら、時刻より後ろなので、最後の値を返す
	return (*keyframe.rbegin()).value;
}

/// <summary>
/// 任意の時刻の値を取得する
/// </summary>
/// <param name="keyframe"></param>
/// <param name="time"></param>
/// <returns></returns>
Quaternion CalcuateValue(const std::vector<KeyFrameQuaternion>& keyframe, float time)
{
	// キーがないと返す値が内のでアウト
	assert(!keyframe.empty());

	// キーが一つか、時刻がキーフレーム前なら最初の値とする
	if (keyframe.size() == 1 || time <= keyframe[0].time)
	{
		return keyframe[0].value;
	}

	for (size_t index = 0; index < keyframe.size() - 1; ++index)
	{
		size_t nextIndex = index + 1;

		// index と nextIndex
		if (keyframe[index].time <= time && time <= keyframe[nextIndex].time)
		{
			// 範囲内を補完する
			float t = (time - keyframe[index].time) / (keyframe[nextIndex].time - keyframe[index].time);
			return Slerp(keyframe[index].value, keyframe[nextIndex].value, t);
		}
	}

	// ここまで来たら、時刻より後ろなので、最後の値を返す
	return (*keyframe.rbegin()).value;
}