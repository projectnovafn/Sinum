// Copyright (c) 2024 Project Nova LLC

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

#define API_URL @"https://api.novafn.dev";

@interface CustomURLProtocol : NSURLProtocol
@end

@implementation CustomURLProtocol

+ (BOOL)canInitWithRequest:(NSURLRequest *)request 
{
    return !([NSURLProtocol propertyForKey:@"RequestHandled" inRequest:request);
}

+ (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request 
{
    return request;
}

- (void)startLoading 
{
    NSMutableURLRequest* ModifiedRequest = [[self request] mutableCopy];
    NSString* OriginalPath = [ModifiedRequest.URL path];
    NSString* OriginalQuery = [ModifiedRequest.URL query];
    
    NSString* NewBaseURLString = API_URL;
    NSURLComponents* Components = [NSURLComponents componentsWithString:newBaseURLString];
    
    Components.path = OriginalPath;
    if (OriginalQuery)
    {
        Components.query = OriginalQuery;
    }

    [modifiedRequest setURL:Components.URL];
    [NSURLProtocol setProperty:@YES forKey:@"RequestHandled" inRequest:modifiedRequest];
    [[self client] URLProtocol:self wasRedirectedToRequest:modifiedRequest redirectResponse:nil];
}



- (void)stopLoading 
{
}
@end

@interface CustomSessionConfiguration : NSURLSessionConfiguration
@end

@implementation CustomSessionConfiguration

+ (CustomSessionConfiguration *)defaultSessionConfiguration 
{
    CustomSessionConfiguration *configuration = [super defaultSessionConfiguration];
    NSMutableArray *defaultProtocols = [configuration.protocolClasses mutableCopy];
    [defaultProtocols insertObject:[CustomURLProtocol class] atIndex:0];
    configuration.protocolClasses = [defaultProtocols copy];
    return configuration;
}

@end

__attribute__((constructor))
void entry()
{
    [NSURLProtocol registerClass:[CustomURLProtocol class]];
}