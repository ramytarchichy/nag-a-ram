#pragma once

#include <array>
#include <openssl/md5.h>


typedef std::array<unsigned char, 16> md5_result;

template <class T>
md5_result md5(const T& data) noexcept
{
	md5_result res;

    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, data.data(), data.size());
    MD5_Final(res.data(), &ctx);

	return res;
}
