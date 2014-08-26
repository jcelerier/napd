#pragma once

struct Checkable
{
		Checkable(int t):
			timeout(t)
		{
		}

		int timeout;
};
