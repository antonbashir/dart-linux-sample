import 'dart:ffi';

import 'package:linux_interactor/interactor/producer.dart';
import 'package:linux_interactor/linux_interactor.dart';
import 'package:linux_interactor_test/bindings.dart';

late final bindings = SampleBindings(DynamicLibrary.open("native/libsample.so"));

class SampleProducer implements NativeProducer {
  late final NativeMethodExecutor sampleCallDart;

  @override
  void initialize(NativeProducerExecutor executor) {
    sampleCallDart = executor.register(bindings.addresses.sample_call_dart);
  }
}

Future<void> main(List<String> args) async {
  final interactor = Interactor();
  final worker = InteractorWorker(interactor.worker(InteractorDefaults.worker()));
  await worker.initialize();
  final producer = worker.producer(SampleProducer());
  final native = bindings.sample_interactor_initialize();
  worker.activate();
  final future = producer.sampleCallDart(
    native.ref.descriptor,
    configurator: (message) => message
      ..allocateOutputString(64)
      ..setInputString("I am Dart"),
  );
  while (!bindings.sample_check_dart(native)) {
    await Future.delayed(Duration.zero);
  }
  final result = await future;
  print(result.outputString);
  result.releaseInputString();
  result.releaseOutputString();
  result.release();
  bindings.sample_interactor_destroy(native);
  await interactor.shutdown();
}
