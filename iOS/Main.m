// Copyright (c) 2025 Project Nova LLC

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

#define API_URL @"http://api.82.25.35.206:4526"
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
    NSString* newBaseURLString = API_URL;

    NSURLComponents* components = [NSURLComponents componentsWithString:newBaseURLString];
    components.path = originalPath;

    NSURLComponents *originalComponents = [NSURLComponents componentsWithURL:modifiedRequest.URL resolvingAgainstBaseURL:NO];
    if (originalComponents.queryItems.count > 0) {
        NSMutableArray<NSURLQueryItem *> *cleanItems = [NSMutableArray array];
        for (NSURLQueryItem *item in originalComponents.queryItems) {
            NSString *decodedValue = item.value ? [item.value stringByRemovingPercentEncoding] : nil;
            [cleanItems addObject:[NSURLQueryItem queryItemWithName:item.name value:decodedValue]];
        }
        components.queryItems = cleanItems;
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
