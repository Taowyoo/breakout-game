#if !defined(BASE_RESOURCE_HPP)
#define BASE_RESOURCE_HPP
#include <string>

class BaseResource {
 private:
  std::string resourceFileName;

 public:
  BaseResource(const std::string& resourceFileName, void* args)
      : resourceFileName(resourceFileName){};
  const std::string& GetResourceFileName() const { return resourceFileName; }
  virtual ~BaseResource(){};
  virtual void LoadFromFile(const std::string& resourcePath, void* args) {}
};

#endif  // BASE_RESOURCE_HPP
