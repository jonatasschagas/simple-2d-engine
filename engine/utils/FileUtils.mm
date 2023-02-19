#import <Foundation/Foundation.h>
#include "FileUtils.h"
#include <string>

@interface FileUtils:NSObject {
}

- (NSString*)loadJSONString: (NSString*) fileName;
- (NSArray*)readLines: (NSString*) fileName withFileType:(NSString*)fileType;

@end

@implementation FileUtils

- (NSString*)loadJSONString: (NSString*) fileName {
    // removing the .json from the filename
    fileName = [fileName stringByReplacingOccurrencesOfString:@".json"
                                                    withString:@""];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:fileName ofType:@"json"];
    NSError* error = nil;
    NSString* content = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&error];
    
    if (error)
    {
        NSLog(@"%@", [error description]);
        return @"";
    }
    
    NSLog(@"Loaded %@\n", fileName);
    return content;
}

- (NSArray*)readLines: (NSString*) fileName withFileType:(NSString*)fileType
{
    fileName = [fileName stringByReplacingOccurrencesOfString:fileType
                                                    withString:@""];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:fileName ofType:fileType];
    NSError* error = nil;
    NSString* content = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&error];
    
    if (error)
    {
        NSLog(@"%@", [error description]);
        return nil;
    }

    // first, separate by new line
    NSArray* allLinedStrings =
          [content componentsSeparatedByCharactersInSet:
          [NSCharacterSet newlineCharacterSet]];
    
    return allLinedStrings;
}

@end

string loadJSONString(string fileName)
{
    NSString *fileNameNS = [NSString stringWithCString:fileName.c_str() encoding:[NSString defaultCStringEncoding]];
    FileUtils* fileUtils = [[FileUtils alloc] init];
    return std::string([[fileUtils loadJSONString:fileNameNS] UTF8String]);
}

vector<string> readLinesFromFile(string fileName, string fileType)
{
    NSString *fileNameNS = [NSString stringWithCString:fileName.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *fileTypeNS = [NSString stringWithCString:fileType.c_str() encoding:[NSString defaultCStringEncoding]];
    
    vector<string> lines;
    
    FileUtils* fileUtils = [[FileUtils alloc] init];
    NSArray* linesNSArr = [fileUtils readLines:fileNameNS withFileType:fileTypeNS];
    
    for (NSString* line in linesNSArr)
    {
        lines.push_back(std::string([line UTF8String]));
    }
    
    return lines;
}
