//
//  SleepManager.h
//  InstantSDK
//
//  Created by Emberify_Vijay on 18/09/17.
//  Copyright © 2017 Emberify. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMotion/CoreMotion.h>
#import <HealthKit/HealthKit.h>
#import "LocationNameAndTime.h"

@protocol SleepManagerDelegate;
@interface SleepManager : NSObject<NSURLSessionDelegate>
/*!
 * @discussion Creates sleep manager singletone class. It has all sleep related information. It can be accessed anywhere in application.
 */
+(SleepManager *)sharedSleepManager;
@property(strong,nonatomic)CMMotionActivityManager *sleepActivity;
@property(strong,nonatomic)NSDateFormatter *dateFormatter;
@property(strong,nonatomic) HKHealthStore *healthStore;


/*!
 * @discussion start sleep tracking using CoreMotion Framework. if start sleep tracking successfully handler returns 1 otherwise handler returns 0.
 
 */
-(void)startCoreMotionSleepTracking:(void(^)(NSInteger status))handler;

/*!
 * @discussion stop sleep tracking using CoreMotion Framework. if stop sleep tracking successfully handler returns Yes otherwise handler returns No.
 
 */
-(void)stopCoreMotionSleepTracking:(void(^)(BOOL isStop))handler;

/*!
 * @discussion start sleep tracking using HealthKit Framework. if start sleep tracking successfully handler returns 1 otherwise handler returns 0.
 
 */
-(void)startHealthKitSleepTracking:(void(^)(NSInteger status))handler;

/*!
 * @discussion stop sleep tracking using HealthKit. if stop sleep tracking successfully handler returns 1 otherwise handler returns 0.
 
 */
-(void)stopHealthKitSleepTracking:(void(^)(BOOL isStop))handler;

/*!
 * @discussion Get sleep data from CoreMotion framework using passed start time and end time.if get sleep data array then returns YES otherwise NO
 * @param startTime passing sleep start date and time.
 * @param endTime passing sleep end date and time.
 */
-(void)getSleepDataUsingCoreMotionFromStartTime:(NSDate *)startTime toEndTime:(NSDate *)endTime withCallBack:(void(^)(BOOL  isSleepData))sleepActivity;


/*!
 * @discussion Get sleep time from sleep data using passed start time and end time.insert and update sleep record in sleep table .if calculate sleep time successfully returns YES otherwise NO.
 * @param startTime passing sleep start date and time.
 * @param endTime passing sleep end date and time.
 */
-(void)getSleepTimeFromSleepData:(NSArray *)sleepData startTime:(NSDate *)startTime endTime:(NSDate *)endTime toQueue:(NSOperationQueue *)sleepQueue withComplitionHandler:(void(^)(BOOL isGetSleepTime))sleepTime;


/*!
 * @discussion Get enable sleep option and pasrse sleep data of selected option.
 * @param startTime passing sleep start date and time.
 * @param toEndTime passing sleep end date and time.
 */
-(void)getSleepOptionAndFindSleepDataFromStartTime:(NSDate *)startTime toEndTime:(NSDate *)toEndTime;

/*!
 * @discussion Create dictionary of date, total sleep time, sleepAt, wokeUpAt, inBetweenDuration, countInBetween, zeroSleep for inserting or update into sleep table of database.
 * @param date passing sleep date.
 * @param totalSleepTime passing total sleep time.
 * @param sleepAtTime passing sleepAt time.
 * @param wokeUpAtTime passing wokeUpAt time.
 * @param inBetweenDuration passing sleep inBetween time.
 * @param countInBetween passing inBetween wakeup count.
 */
-(void)storeDataInDictionaryDate:(NSString *)date totalSleepTime:(int )totalSleepTime sleepAtTime:(NSDate *)sleepAtTime wokeUpAtTime:(NSDate *)wokeUpAtTime inBetweenDuration:(int)inBetweenDuration countInBetween:(int)countInBetween zeroSleep:(int)zeroSleep withCallBackHandler:(void(^)(BOOL isStore))storeHandler;

#pragma mark -HealthKit

/*!
 * @discussion Get healthkit permission for parsing sleep data from healthkit.
 */
-(void)healthKitPermission:(void(^)(BOOL healthKitPermission))permissionHandler;


/*!
 * @discussion Get sleep data from healthKit framework using passed start time and end time.if get sleep data array then returns YES otherwise NO
 * @param startTime passing sleep start date and time.
 * @param endTime passing sleep end date and time.
 */
-(void)getSleepDataUsingHealthKit:(NSDate *)startTime toEndTime:(NSDate *)endTime withCallBack:(void(^)(BOOL  isSleepData))healthKitSleepActivity;


#pragma mark -FitBit
/*!
 * @discussion Get sleep data from FitBit framework using passed start time.if get sleep data array then returns YES otherwise NO
 * @param startTime passing sleep start date and time.
 */
-(void)getSleepDataUsingFitBit:(NSDate *)startTime  withCallBack:(void(^)(BOOL  isSleepData))FitBitSleepActivity;

/*!
 * @discussion getting n number of days of sleep and insert n number of sleep  data into sleep table
 
 */
-(void)getNNumberOfSleepData;


/*!
 * @discussion finding a last midnight using passed date.
 * @param date .
 * @return midnight date using passed date.
 */
-(NSDate *)midNightOfLastNight :(NSDate *)date;

/*!
 * @discussion find next midnight using passed date.
 * @param date .
 * @return next midnight using passed date.
 */

-(NSDate *)nextMidNight:(NSDate *)date;

/*!
 * @discussion activity custome delegate for showing permission alert on UI .
 
 */

@property(nonatomic,weak)id<SleepManagerDelegate> delegate;
@end

@protocol SleepManagerDelegate <NSObject>

@optional
-(void)showSleepData:(LocationNameAndTime *)sleepData;

-(void)showSleepPermissionAlert:(NSString *)alertTitle alertBody:(NSString *)alertBody;

@end