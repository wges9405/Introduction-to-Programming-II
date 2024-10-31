#ifndef _FUNC_H
#define _FUNC_H
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

class Codec {
public:
    virtual void encode() = 0;
    virtual void decode() = 0;
    virtual ~Codec() { } // Do nothing
    virtual void show(std::ostream& os) const = 0;
    virtual bool is_encoded() const = 0;
};

class DummyCodec: public Codec {
public:
    DummyCodec(std::string s): encoded{false}, code_str{s} { }

    void encode() {
        encoded = true;
    }

    void decode() {
        encoded = false;
    }

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }

private:
    bool encoded;
    std::string code_str;
};

class RleCodec: public Codec
{
public:
    RleCodec(std::string s): encoded{false}, code_str{s} { }

    void encode();

    void decode();

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }


private:
    bool encoded;
    std::string code_str;
};

void RleCodec::encode()
{
    std::stringstream os;
    char prev = '\0';
    int cnt = 0;
    for (auto c : code_str) {
        if (c != prev) {
				if (cnt > 2) os << cnt << prev;
				else 
					for (int i = 0 ; i < cnt ; i++)
						os << prev;
            prev = c;
            cnt = 1;
        }
        else cnt++;
    }
		if (cnt > 2) os << cnt << prev;
		else
			for (int i = 0 ; i < cnt ; i++)
				os << prev;

    code_str = os.str();
	encoded = true;
}

void RleCodec::decode()
{
	std::stringstream os;
	std::string int_str;
	for (auto c : code_str) {
		if (std::isdigit(c)) {
			int_str.push_back(c);
		} else {
			int cnt = 0;
			std::stringstream is{int_str};
			is >> cnt;
			if (cnt==0) {
				os << c;
			} else {
				for (int i=0; i<cnt; ++i)
					os << c;
			}
			int_str.clear();
		}
	}

	code_str = os.str();
	encoded = false;
}
/*
I:
AAADDDDDDDBBGGGGGCEEEE
O:
Dummy encoding: AAADDDDDDDBBGGGGGCEEEE
Dummy decoding: AAADDDDDDDBBGGGGGCEEEE
RLE encoding: 3A7DBB5GC4E
RLE decoding: AAADDDDDDDBBGGGGGCEEEE
*/
#endif
