// Copyright (c) 2024 Project Nova LLC

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

#define API_URL @"https://api.novafn.dev"
#define EPIC_GAMES_URL @"ol.epicgames.com"

@interface CustomURLProtocol : NSURLProtocol
@end

@implementation CustomURLProtocol

+ (BOOL)canInitWithRequest:(NSURLRequest *)request 
{  
    NSString *absoluteURLString = [[request URL] absoluteString];
    if ([absoluteURLString containsString:EPIC_GAMES_URL] && ![absoluteURLString containsString:@"/CloudDir/"]) {
        if ([NSURLProtocol propertyForKey:@"Handled" inRequest:request]) {
            return NO;
        }
        return YES;
    }
    return NO;
}

+ (NSURLRequest*)canonicalRequestForRequest:(NSURLRequest*)request
{
    return request;
}

- (void)startLoading
{
    NSMutableURLRequest* modifiedRequest = [[self request] mutableCopy];

    NSString* originalPath = [modifiedRequest.URL path];
    NSString* originalQuery = [modifiedRequest.URL query];

    NSString* newBaseURLString = API_URL;
    NSURLComponents* components = [NSURLComponents componentsWithString:newBaseURLString];

    components.path = originalPath;
    if (originalQuery)
    {
        components.query = originalQuery;
    }

    [modifiedRequest setURL:components.URL];
    [NSURLProtocol setProperty:@YES forKey:@"Handled" inRequest:modifiedRequest];

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnonnull"
    [[self client] URLProtocol:self
        wasRedirectedToRequest:modifiedRequest
              redirectResponse:nil];
#pragma clang diagnostic pop
}

- (void)stopLoading
{
}
@end

__attribute__((constructor)) void entry()
{
    [NSURLProtocol registerClass:[CustomURLProtocol class]];
}