//
//  ELog.m
//  Sparkle
//
//  Created by Eric Shapiro on 1/3/22.
//  Copyright © 2022 Sparkle Project. All rights reserved.
//

#import "ELog.h"

NSString *NSDataToHex(NSData *data);

NSString *NSDataToHex(NSData *data) {
    if ( data == nil || data.length == 0 )
        return @"[empty]";

    NSUInteger capacity = data.length * 2;
    NSMutableString *sbuf = [NSMutableString stringWithCapacity:capacity];
        
    const unsigned char *buf = data.bytes;
    NSUInteger i;
    for (i=0; i<data.length; ++i) {
      [sbuf appendFormat:@"%02X", (int)buf[i]];
    }
    return sbuf;
}

void ELog(NSDictionary *dict) {
    NSString *token = @"9bcc861f-6d26-4a2b-8dec-88188cb8054b";      // AppVision token - delete when done
    NSString *urlString = @"https://logs-01.loggly.com/inputs/TOKEN/tag/http/";
    urlString = [urlString stringByReplacingOccurrencesOfString:@"TOKEN" withString:token];
    
    NSError *error = nil; 
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict 
                            options:NSJSONWritingPrettyPrinted
                            error:&error];
    if ( error ) {
        NSLog( @"Loggly error: %@", error.localizedDescription);
    }
    else {
        NSLog( @"Loggly success:");
    }
    NSString *logString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    NSLog( @"%@", logString );
    
    NSURL *url = [NSURL URLWithString:urlString];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    request.HTTPMethod = @"POST";
    request.HTTPBody = jsonData;
    [request addValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    [request addValue:@"application/json" forHTTPHeaderField:@"Accept"];
    //[request addValue:token forHTTPHeaderField:@"Authorization"];
    NSURLSessionDataTask *task = [NSURLSession.sharedSession dataTaskWithRequest:request];
    [task resume];
}

void ELogURL( NSString *title, NSURL *url ) {
    NSString *urlString = @"n/a";
    if (url != nil) {
        urlString = [url description];
    }
    ELog( @{@"Title" : title, @"Data" : urlString} );
}

void ELogString( NSString *title, NSString *str ) {
    if ( str == nil ) 
        str = @"";
        
    ELog( @{@"Title" : title, @"Data" : str} );
}

void ELogData( NSString *title, NSData *data ) {
    ELog( @{@"Title" : title, @"Data" : NSDataToHex(data)} );
}

void ELogError( NSString *title, NSError *error ) {
    if ( error == nil )
        ELog( @{@"Title" : title, @"Data" : @"No error"} );
    else
        ELog( @{@"Title" : title, @"Data" : error.localizedDescription} );
}

