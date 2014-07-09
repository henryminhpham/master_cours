//
//  myCustomAnnotation.h
//  iSouvenir
//
//  Created by m2sar on 04/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MapKit.h>

@interface myCustomAnnotation : NSObject <MKAnnotation> {
    CLLocationCoordinate2D coordinate;
}
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;
- (id)initWithLocation:(CLLocationCoordinate2D)coord;
@property (nonatomic, copy) NSString *title;

@end
