//
//  ViewController.m
//  weakStrong
//
//  Created by chenjingting on 2023/10/10.
//

#import "ViewController.h"
#import "MacroDefine.h"

#ifndef weakify
#define weakify(object) __weak __typeof__(object) object##_##weak_ = object;
#endif

#ifndef strongify
#define strongify(object) __strong __typeof__(object) object = object##_##weak_;
#endif

@interface TestObject : NSObject
@end

@interface ViewController ()

@property (nonatomic, copy) void(^actionBlock)(void);
@property (nonatomic, copy) void(^actionBlock1)(void);

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.

    TestObject *object = [[TestObject alloc] init];

//    __weak __typeof(self) self_weak_ = self;
    weakify(self, object)
    self.actionBlock = ^{
//        __strong __typeof(self) self = self_weak_;
        strongify(self, object)
        [self doSomething];
        [self doSomethingWithObject:object];
        
        
        self.actionBlock1 = ^{
            strongify(self)
//            __strong __typeof(self) self = self_weak_;
            [self doSomething];
        };
    };
}

- (void)doSomething {}

- (void)doSomethingWithObject:(NSObject *)object {}

@end

@implementation TestObject
@end
