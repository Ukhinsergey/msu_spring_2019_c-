#pragma once

enum class Error
{
    NoError,
    CorruptedArchive
};


class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... Args>
    Error operator()(Args&&... args)
    {
        return process(std::forward<Args>(args)...);
    }
    
private:
    std::ostream& out_;

    template <class t>
    Error process(t&& val) {
        //std::cout << val << std::endl;
        return write(std::forward<t>(val));
    }

    template <class t, class ... Args>
    Error process(t&& val, Args&&... args) {
        if (process(std::forward<t>(val))== Error::NoError &&  process(std::forward<Args>(args)...) == Error::NoError) {
            return Error::NoError;
        }
        return Error::CorruptedArchive;
    }

    

    Error write(const bool& val) {
        //std::cout << "second" << std::endl;
        if (val) {
            out_ << "true" << Separator;
            return Error::NoError;
        } else {
            out_ << "false" << Separator;
            return Error::NoError;
        }
    }

    Error write(const uint64_t& val) {
        //std::cout << "third" << std::endl;
        out_ << val << Separator;
        return Error::NoError;
    }

    template <class t>
    Error write(const t& val) {
        //std::cout << "first" << std::endl;
        return Error::CorruptedArchive;
    }


};


class Deserializer
{
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... Args>
    Error operator()(Args&&... args)
    {
        return process(std::forward<Args>(args)...);
    }
    
private:
    std::istream& in_;

    template <class t>
    Error process(t&& val) {
        return read(std::forward<t>(val));
    }

    template <class t, class ... Args>
    Error process(t&& val, Args&&... args) {
        if (process(std::forward<t>(val))== Error::NoError &&  process(std::forward<Args>(args)...) == Error::NoError) {
            return Error::NoError;
        }
        return Error::CorruptedArchive;
    }

    template <class t>
    Error read(t& val) {
        return Error::CorruptedArchive;
    }

    Error read(bool& val) {
        std::string text;
        in_ >> text;
        if (text == "true") {
            val = true;
            return Error::NoError;
        } else  if (text == "false"){
            val = false;
            return Error::NoError;
        }
        return Error::CorruptedArchive;
    }

    Error read(uint64_t& val) {
        std::string text;
        in_ >> text;
        size_t pos = 0;
        if (text[0] == '-') {
            return Error::CorruptedArchive;
        }
        try {
            val = std::stoull(text);
        } catch (const std::invalid_argument &ex) {
            return Error::CorruptedArchive;
        }
        return Error:: NoError;
    }


};