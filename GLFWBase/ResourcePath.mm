#include "ResourcePath.h"
#import <Cocoa/Cocoa.h>

std::string getResourcePath(std::string name, std::string fileEnding) {
    NSString *nameString = [NSString stringWithCString:name.c_str() encoding:NSUTF8StringEncoding];
    NSString *endingString = [NSString stringWithCString:fileEnding.c_str() encoding:NSUTF8StringEncoding];
    NSString *resourcePath = [[NSBundle mainBundle] pathForResource:nameString ofType:endingString];
    if(resourcePath) {
        return std::string([resourcePath cStringUsingEncoding:NSUTF8StringEncoding]);
    } else {
        printf("Can't find resource path: %s.%s\n", name.c_str(), fileEnding.c_str());
        return "";
    }
}
