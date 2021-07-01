
unsigned int hashModulus(unsigned int k, unsigned int m)
{
	return (k % m);
}

unsigned int hashMurmur(const char* key, unsigned int len, unsigned int seed)
{
	unsigned int h = seed;

	//Key chunks
	if (len > 3)
	{
		const unsigned int* key_x4 = (const int*)key;
		int i = len >> 2;
		do {
			unsigned int k = *key_x4;
			//Linee 3..9 pseudo-code
			k *= 0XCC9E2d51;
			k = (k >> 17) | (k << 15);
			k *= 0x18873593;
			h = h ^ k;
			h = (h >> 19) | (h << 13);
			h = (h * 5) + 0xE6546B64;
			key_x4++;
		} while (--i);
		key = (const char*)key_x4;
	}
	//---

	//Trailing chunk
	if (len & 3) //len non � un multiplo di 4
	{
		int i = len & 3;
		unsigned int t = 0;
		key = &key[i - 1];
		do
		{
			t <<= 8;
			t |= *key;
			key--;
		} while (--i);
		//Linee 12..15 pseudo-code
		t = t * 0xCC9E2D51;
		t = (t >> 17) | (t << 15);
		t = t * 0X1B873593;
		h ^= t;
	}
	//---

	//Avalanche
	//Linee 16..21 pseudo-code
	h ^= len;
	h ^= h >> 16;
	h *= 0X85EBCA6B;
	h ^= h >> 13;
	h *= 0xC2B2AE35;
	h = h >> 16;
	//---

	return h;
}