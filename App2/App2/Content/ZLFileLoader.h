#pragma once
class ZLFileLoader {
public:
	ZLFileLoader();
	~ZLFileLoader()
	{

	}
	Platform::Array<byte>^ ReadData(Platform::String^ filename);
};