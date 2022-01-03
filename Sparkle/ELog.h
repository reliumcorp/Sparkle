//
//  ELog.h
//  Sparkle
//
//  Created by Eric Shapiro on 1/3/22.
//  Copyright © 2022 Sparkle Project. All rights reserved.
//

#import <Foundation/Foundation.h>

void ELog(NSDictionary *dict);
void ELogURL( NSString *title, NSURL *url );
void ELogString( NSString *title, NSString *str );
void ELogData( NSString *title, NSData *data );
void ELogError( NSString *title, NSError *error );

