#pragma once

class Living
{
public:
	Living();

	virtual ~Living() = default;

	bool isLive() const;
protected:
	bool isLive_;
};